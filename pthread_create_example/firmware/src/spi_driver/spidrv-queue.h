#ifndef SPIDRV_QUEUE_
#define SPIDRV_QUEUE_

/* DO NOT MODIFY: generated from spi_async_driver.c */

#include <stdint.h>
#include <stdbool.h>
#include "spi_async_driver.h"

struct SpiDrvEntry {
    SpiDrvAsync_TransferCB_t pCallback;
    uint8_t txBufferStatic[DRV_NON_ZERO_CPY_BUF_SIZE];
    uint8_t rxBufferStatic[DRV_NON_ZERO_CPY_BUF_SIZE];
    const uint8_t *txBuffer;
    uint8_t *rxBuffer;
    void *tag;
    DRV_SPI_TRANSFER_EVENT event;
    uint32_t gpioMask;
    uint16_t length;
    uint8_t csInstance;
    bool useStaticTx;
    bool useStaticRx;
};

/*
 * namespace: qspidrv
 * type: "struct SpiDrvEntry"
 * stages: enqueue send interrupt event
 */

#ifdef __cplusplus
extern "C" {
#endif

struct qspidrv_queue {
    struct SpiDrvEntry *buffer_;
    unsigned size_;
    unsigned enqueue_, send_, interrupt_, event_;
};

static inline void init_qspidrv_queue(struct qspidrv_queue *q, struct SpiDrvEntry *buffer, unsigned size)
    { q->buffer_ = buffer; q->size_ = size; q->enqueue_ = q->send_ = q->interrupt_ = q->event_ = 0; }

/* enqueue */
static inline int qspidrv_enqueue_ready(struct qspidrv_queue const *q) {
    return q->enqueue_ - q->event_ < q->size_; }
static inline struct SpiDrvEntry *qspidrv_enqueue_ptr(struct qspidrv_queue const *q) {
    return q->buffer_ + (q->enqueue_ & (q->size_ - 1)); }
static inline void qspidrv_enqueue_done(struct qspidrv_queue *q) {
    ++q->enqueue_; }

/* send */
static inline int qspidrv_send_ready(struct qspidrv_queue const *q) {
    return q->enqueue_ - q->send_ - 1 < q->size_; }
static inline struct SpiDrvEntry *qspidrv_send_ptr(struct qspidrv_queue const *q) {
    return q->buffer_ + (q->send_ & (q->size_ - 1)); }
static inline void qspidrv_send_done(struct qspidrv_queue *q) {
    ++q->send_; }
static inline void qspidrv_send_undo(struct qspidrv_queue *q) {
    --q->send_; }

/* interrupt */
static inline int qspidrv_interrupt_ready(struct qspidrv_queue const *q) {
    return q->send_ - q->interrupt_ - 1 < q->size_; }
static inline struct SpiDrvEntry *qspidrv_interrupt_ptr(struct qspidrv_queue const *q) {
    return q->buffer_ + (q->interrupt_ & (q->size_ - 1)); }
static inline void qspidrv_interrupt_done(struct qspidrv_queue *q) {
    ++q->interrupt_; }

/* event */
static inline int qspidrv_event_ready(struct qspidrv_queue const *q) {
    return q->interrupt_ - q->event_ - 1 < q->size_; }
static inline struct SpiDrvEntry *qspidrv_event_ptr(struct qspidrv_queue const *q) {
    return q->buffer_ + (q->event_ & (q->size_ - 1)); }
static inline void qspidrv_event_done(struct qspidrv_queue *q) {
    ++q->event_; }

#ifdef __cplusplus
}
#endif

#endif /* SPIDRV_QUEUE_ */

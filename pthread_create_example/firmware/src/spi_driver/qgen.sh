#!/bin/bash

# This generates queues for the project.

# Usage:
#  - stick into the c-source file a script like in example below;
#  - call qgen.sh <SOURCE-FILE-NAME>

# Source file script example:
#
#  #ifdef QGEN_
#  $ {
#
#  #include <stdint.h>
#
#  struct qrxspibuf {
#      uint8_t buff[BUFF_SIZE];
#  };
#
#  $ generate_queue qrxspibuf "struct qrxspibuf" alloc receive enqueue free
#
#  $ } | mk_include "${D}/.generated/qrxspibuf_queue.h" "QRXSPIBUF_QUEUE_"
#  #endif

gen_stage_body(){
    local name=$1
    local check_cond="$2"
    echo "/* ${name} */"
    echo "static inline int ${NS}_${name}_ready(struct ${NS}_queue const *q) {"
    [ -z "${TR:-}" ] ||
        echo "    printf(\"${TR}: %s(): %d\n\", __func__, ${check_cond});"
    echo "    return ${check_cond}; }"
    echo "static inline ${T} *${NS}_${name}_ptr(struct ${NS}_queue const *q) {"
    echo "    return q->buffer_ + (q->${name}_ & (q->size_ - 1)); }"
    echo "static inline void ${NS}_${name}_done(struct ${NS}_queue *q) {"
    [ -z "${TR:-}" ] ||
        echo "    printf(\"${TR}: %s()\n\", __func__);"
    echo "    ++q->${name}_; }"
    echo ""
}

gen_first_stage(){
    local name=$1
    local last=$2
    gen_stage_body ${name} "q->${name}_ - q->${last}_ < q->size_"
}

gen_other_stage(){
    local name=$1
    local prev=$2
    gen_stage_body ${name} "q->${prev}_ - q->${name}_ - 1 < q->size_"
}

generate_queue(){
    local NS=${1:?missing namespace}
    local T="${2:?missing type}"
    local FF=(${3:?missing stages})

    shift 3
    while [ -n "${1:-}" ]; do FF+=($1); shift; done

    echo "/*"
    echo " * namespace: $NS"
    echo " * type: \"$T\""
    echo " * stages: ${FF[@]}"
    echo " */"
    echo ""

    echo "#ifdef __cplusplus"
    echo "extern \"C\" {"
    echo "#endif"
    echo ""

    echo "struct ${NS}_queue {"
    echo "    ${T} *buffer_;"
    echo "    unsigned size_;"
    echo -n "    unsigned ${FF[0]}_"
    for i in "${FF[@]:1}"; do echo -n ", ${i}_"; done
    echo ";"
    echo "};"
    echo ""

    echo "static inline void init_${NS}_queue(struct ${NS}_queue *q, ${T} *buffer, unsigned size)"
    echo -n "    { q->buffer_ = buffer; q->size_ = size;"
    for i in "${FF[@]}"; do echo -n " q->${i}_ ="; done
    echo " 0; }"
    echo ""

    gen_first_stage ${FF[0]} ${FF[-1]}

    for i in $(seq 1 $(( ${#FF[@]} - 1 )) ); do
        gen_other_stage ${FF[$i]} ${FF[$(($i-1))]}
    done

    echo "#ifdef __cplusplus"
    echo "}"
    echo "#endif"
}

mk_include(){
    local file="$1"
    local def="${2:-$(mktemp -u -p . -t QUEUE_XXXXXXXXXX_ |sed "s/^..//")}"

    mkdir -p "$(dirname "$file")"

    {
        echo "#ifndef $def"
        echo "#define $def"
        echo ""
        echo "/* DO NOT MODIFY: generated from $src_file */"
        cat
        echo "#endif /* $def */"
    } >"$file"
}

pr_(){
    printf "%s\n" "$1"
}

transf_(){
    sed -n "/^#if.*\<QGEN_\>/,/#endif/p" | # select lines between '#if QGEN_' and '#endif'
    sed -n "/^[$] {/,/^[$] }/p" | # select lines between '$ {' and '$ }'
    sed "s,^, ,;s,^ [$],$," | # add space for c-code
    sed "/^ /s,','\"'\"',g" | # escape '
    sed "/^ /s,^ , pr_ ',;/^ /s,$,'," | # final wrap c-code
    sed "/^[$]/s,^.,," | # remove command markers
    cat
}

# "trace tx generate_queue .." enables traces

trace(){
    local TR="$1"
    "${@:2}"
}

src_file="${1:?expect source file name}"
D="$(dirname "$src_file")"
source <(cat "$src_file" |transf_)

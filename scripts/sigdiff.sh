#!/usr/bin/env bash
#
#   usage: ./sigdiff_color.sh old.txt new.txt [tolerance] [ignore_regex]
#
#   tolerance     – абсолютный порог для чисел  (по умолчанию 1e-9)
#   ignore_regex  – токены, которые сравнивать не нужно
#                   (по умолчанию "^(Its=|Count=)")
#
#   вывод:        пары «существенно разных» строк с цветовой подсветкой
#

set -euo pipefail

if [[ $# -lt 2 ]]; then
  echo "usage: $0 old_output new_output [tolerance] [ignore_regex]" >&2
  exit 1
fi

F1="$1"
F2="$2"
TOL="${3:-1e-9}"
IGN_RE="${4:-^(Its=|Count=)}"          # изменить, если нужно другие поля игнорировать

# ANSI-коды цветов
RED=$'\033[31m'
GRN=$'\033[32m'
RST=$'\033[0m'

awk -v f2="$F2" -v tol="$TOL" -v ign="$IGN_RE" -v red="$RED" -v grn="$GRN" -v rst="$RST" '
  function abs(x){ return (x<0)?-x:x }
  function isnum(s){ return (s ~ /^[+-]?[0-9]+([.][0-9]+)?([eE][+-]?[0-9]+)?$/) }

  {
    getline line2 < f2
    split($0,  a, " ")
    split(line2, b, " ")

    maxlen = (length(a) > length(b) ? length(a) : length(b))
    significant = 0

    # подготовим раскрашенные копии
    for (i=1;i<=maxlen;++i){
        tokenA = (i in a ? a[i] : "<MISSING>")
        tokenB = (i in b ? b[i] : "<MISSING>")

        if (tokenA == tokenB) { cA[i]=tokenA; cB[i]=tokenB; continue }

        if (ign != "" && (tokenA ~ ign || tokenB ~ ign)) { cA[i]=tokenA; cB[i]=tokenB; continue }

        if (isnum(tokenA) && isnum(tokenB) && abs(tokenA-tokenB) <= tol) {
            cA[i]=tokenA; cB[i]=tokenB; continue
        }

        # токены действительно различаются
        significant = 1
        cA[i]=red tokenA rst
        cB[i]=grn tokenB rst
    }

    if (significant) {
        # склеиваем обратно
        outA=""; outB=""
        for (i=1;i<=maxlen;++i){ outA=outA (i in cA?cA[i]:"") (i<maxlen?" ":"") }
        for (i=1;i<=maxlen;++i){ outB=outB (i in cB?cB[i]:"") (i<maxlen?" ":"") }
        printf "<<< %s\n>>> %s\n\n", outA, outB
    }
  }

  END {
    if ((getline rest < f2) > 0) {
        print "⚠️  второй файл длиннее — есть необработанные строки." > "/dev/stderr"
    }
  }
' "$F1"


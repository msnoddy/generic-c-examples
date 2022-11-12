#! /usr/bin/env bash
set -e

scriptPath=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

function main() {
  local binName="generic-stack"

  rm -f "${binName}"

  gcc -std=c17 stack.c main.c -I "${scriptPath}" -o "${binName}"

  chmod +x "${binName}"
}

main "$@"

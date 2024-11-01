#!/bin/bash
### these values are defined in settings.json
readonly TARGET_IP="$1"
readonly DEBUG_PORT="$2"
readonly BINARY="$4"  # change this to project name variable
readonly TARGET_DIR="$5"

echo "starting gdb debugging"
echo "starting gdb server on target"
echo "target ip: ${TARGET_IP}"
echo "target dir: ${TARGET_DIR}"
echo "binary: ${BINARY}"
# start gdbserver on target
ssh -t root@${TARGET_IP} "sh -c 'cd ${TARGET_DIR}; gdbserver localhost:${DEBUG_PORT} ${TARGET_DIR}/${BINARY}'"

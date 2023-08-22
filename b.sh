#!/bin/bash
cd ..
fn=helloos."`date +"%m.%d"`".tgz
if [ -f "${fn}" ]; then
    echo "${fn} exists. remove old ${fn}"
    rm -fv "${fn}"
fi

tar zcf ${fn} helloos
ls -lht ${fn}

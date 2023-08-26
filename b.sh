#!/bin/bash
cd ..
fn=helloos."`date +"%m.%d"`".tgz
if [ -f "${fn}" ]; then
    echo "${fn} exists. remove old ${fn}"
    rm -fv "${fn}"
fi

tar zcf ${fn} --exclude='helloos/.git' helloos
ls -lht ${fn}
tar tf ${fn}

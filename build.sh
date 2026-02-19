#!/usr/bin/env bash

CURRENT_DIR=$(pwd)
ROOT_DIR=$(echo "$CURRENT_DIR" | grep -o .*/TSU_PB_labs_linux64ver)

if ! [[ -d $ROOT_DIR/bin ]]; then
    mkdir $ROOT_DIR/bin \
    && echo "Создан каталог bin"
fi

if [[ $1 != "-a" ]]; then
	PATH_IN="$(echo $1 | sed 's|\./||')" # ./dir/test.ccp -> dir/test.cpp
    NAME_IN="$(basename $1)"
	NAME_OUT="$(basename $1 | sed 's|\.cpp|\.out|')" # ./test.ccp -> test.out
    NAME_MOVED="$(echo $NAME_OUT | sed 's|\.out||')" # test.out -> test

    printf %s "Компиляция $NAME_IN...   "; g++ -march=native $CURRENT_DIR/$PATH_IN -o $NAME_OUT \
    && echo "завершено ($NAME_IN -> bin/$NAME_MOVED)" && mv $CURRENT_DIR/$NAME_OUT $ROOT_DIR/bin/$NAME_MOVED
else
	PATH_IN="$(echo $2 | sed 's|\./||')"
    NAME_IN="$(basename $2)"
	NAME_OUT="$(basename $2 | sed 's|\.cpp|\.out|')"
    NAME_MOVED="$(echo $NAME_OUT | sed 's|\.out||')"
	
    printf %s "Компиляция $NAME_IN...   "; g++ -march=native $CURRENT_DIR/$PATH_IN -o $NAME_OUT \
	&& echo "завершено ($NAME_IN -> bin/$NAME_MOVED)" && mv $CURRENT_DIR/$NAME_OUT $ROOT_DIR/bin/$NAME_MOVED \
	&& echo -e "bin/$NAME_MOVED\n"; cd $ROOT_DIR/bin && $ROOT_DIR/bin/$NAME_MOVED
fi

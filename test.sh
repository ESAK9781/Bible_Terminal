gcc -Werror -Wall -o ./bin/kjv ./main.c ./lib/bible/bible.c ./lib/vectors/vectors.c ./lib/searchUtil/searchUtil.c -lncurses
cd ./bin
./kjv
cd ..
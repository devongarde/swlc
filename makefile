
all: attribute.o context.o directory.o element.o external.o options.o page.o swlc.o
	ld -L /usr/lib -L ../modest/myhtml-master -L ../../automatic/Library/boost_1_70_0/stage/lib -o swlc *.o -lmyhtml -lboost_filesystem-clang-darwin90-mt-s-x64-1_70 -lboost_program_options-clang-darwin90-mt-s-x64-1_70 -lpthread -lc++ -macosx_version_min 10.13


attribute.h: common.h context.h
	touch attribute.h

context.h: common.h
	touch context.h

directory.h: common.h external.h context.h
	touch directory.h

element.h: attribute.h context.h directory.h
	touch element.h

external.h: context.h
	touch external.h

options.h: common.h context.h
	touch options.h

page.h: directory.h element.h
	touch page.h




attribute.o: attribute.cpp attribute.h
	cc -I../modest/myhtml-master/include -I../../automatic/Library/boost_1_70_0 -g -std=gnu++14 -c attribute.cpp

context.o: context.cpp options.h context.h
	cc -I../modest/myhtml-master/include -I../../automatic/Library/boost_1_70_0 -g -std=gnu++14 -c context.cpp

directory.o: directory.cpp page.h directory.h
	cc -I../modest/myhtml-master/include -I../../automatic/Library/boost_1_70_0 -g -std=gnu++14 -c directory.cpp

element.o: element.cpp element.h
	cc -I../modest/myhtml-master/include -I../../automatic/Library/boost_1_70_0 -g -std=gnu++14 -c element.cpp

external.o: external.cpp common.h external.h
	cc -I../modest/myhtml-master/include -I../../automatic/Library/boost_1_70_0 -g -std=gnu++14 -c external.cpp

options.o: options.cpp version.h options.h
	cc -I../modest/myhtml-master/include -I../../automatic/Library/boost_1_70_0 -g -std=gnu++14 -c options.cpp

page.o: page.cpp common.h page.h
	cc -I../modest/myhtml-master/include -I../../automatic/Library/boost_1_70_0 -g -std=gnu++14 -c page.cpp

swlc.o: swlc.cpp attribute.h common.h context.h directory.h element.h page.h
	cc -I../modest/myhtml-master/include -I../../automatic/Library/boost_1_70_0 -g -std=gnu++14 -c swlc.cpp


clean:
	rm *.o



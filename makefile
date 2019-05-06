
all: attribute.o context.o directory.o element.o external.o options.o page.o swlc.o
	ld -L /usr/lib -L ~/depot/applications/swlc/lib/Release -L ~/depot/automatic/Library/boost_1_70_0/stage/lib -o swlc *.o -lmyhtml -lboost_filesystem-mt-s-x64 -lboost_program_options-mt-s-x64 -lpthread -lc++


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
	cc -g -std=gnu++17 -c attribute.cpp

context.o: context.cpp options.h context.h
	cc -g -std=gnu++17 -c context.cpp

directory.o: directory.cpp page.h directory.h
	cc -g -std=gnu++17 -c directory.cpp

element.o: element.cpp element.h
	cc -g -std=gnu++17 -c element.cpp

external.o: external.cpp common.h external.h
	cc -g -std=gnu++17 -c external.cpp

options.o: options.cpp version.h options.h
	cc -g -std=gnu++17 -c options.cpp

page.o: page.cpp common.h page.h
	cc -g -std=gnu++17 -c page.cpp

swlc.o: swlc.cpp attribute.h common.h context.h directory.h element.h page.h
	cc -g -std=gnu++17 -c swlc.cpp


clean:
	rm *.o


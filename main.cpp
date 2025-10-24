
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <swmgr.h>
#include <swmodule.h>
#include <markupfiltmgr.h>

using namespace::sword;

int main(int argc, char **argv)
{
    setenv("SWDEBUG", "1", 1);

	SWMgr library(new MarkupFilterMgr(FMT_PLAIN));
	SWModule *target;

	if (argc != 3) {
		fprintf(stderr, "\nusage: %s <modname> <\"lookup key\">\n"
							 "\tExample: lookup KJV \"James 1:19\"\n\n", argv[0]);
		exit(-1);
	}


	target = library.getModule(argv[1]);
	if (!target) {
		fprintf(stderr, "Could not find module [%s].  Available modules:\n", argv[1]);
		ModMap::iterator it;
		for (it = library.Modules.begin(); it != library.Modules.end(); it++) {
			fprintf(stderr, "[%s]\t - %s\n", (*it).second->Name(), (*it).second->Description());
		}
		exit(-1);
	}

	target->setKey(argv[2]);

	target->renderText();    // force an entry lookup first to resolve key to something pretty for printing below.

	std::cout << target->getKeyText() << ":\n";
	std::cout << target->renderText();
	std::cout << "\n";
	std::cout << "==========================\n";
	std::cout << std::endl;
	return 0;
}
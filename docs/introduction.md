This is the indrocution documentation for the SWORD Project.

## What is SWORD

> "SWORD is an Application Programming Interface (API) for CrossWire modules. When referring to SWORD it is customary to use all uppercase. It is sometimes referred to as the SWORD engine."

The SWORD project launched in the late 90s by the CrossWire Bible Society, conceived to create a free, open-source software platform for the study of the Bible.

- Cross-Platform Accessibility
- Open Source Collaboration
- Comprehensive Bible Study Resources

Which make it really robust by its on definition, while it continues to evolve, its open-source nature allows developers to contribute enhancements. Still it have plenty of features that the frontends implement (https://wiki.crosswire.org/Choosing_a_SWORD_program).


The community emphasizes the development of new modules, facilitating the expansion of its resource library. However, the API does not currently support plugin architectures or modular extensions. Consequently, developers aiming to introduce new functionalities often need to extend the API directly by implementing additional code using the existing headers.

### What is JSWORD and others similar? 

JSWORD is an implementation of the SWORD API for Java. That said, it should be noted that it is not a port. And it have its own front-end even some for the Android platform!

You can use this project if you want to use the JVM, or platforms like Android. Also I think it should work in languages like Scala.

> Should we make one for rust? 

Also you can learn a lot from this project if you want to implement the project on other language or learn more of it.

### Is this E-SWORD?

No, read the FAQ of the project: https://wiki.crosswire.org/EnduserFAQ#Is_SWORD_the_same_as_e-Sword.3F

Also E-SWORD is propietary so lets open the doors of the bible study with SWORD!

## A CrossWire Module

A “module” in the SWORD ecosystem is essentially a content package: e.g., a Bible translation, a commentary, a lexicon/dictionary, a glossary, daily devotional, general book, map resource, etc. These modules are meant to be used by SWORD-compatible front-ends (programs) which load/display/search them (like Xiphos, BibleTime, etc).

Internally, it have:

-   ".conf" configuration file, which tells the SWORD engine where the data is, what driver to use, metadata like description, language, encoding, license, etc. [Read](https://www.crosswire.org/sword/develop/swordmodule/)

- The actual data files are in certain formats (legacy ones are like GBF, ThML and now OSIS XML) and then are imported/compiled (sometimes compressed) into the module form.

This means a common workflow (for a module creator) The workflow is obtain the source text, convert/markup it, import via SWORD utilities, create the .conf, test in front-ends, optionally submit to CrossWire for inclusion in their repository. And as end user you install this modules using the official repository, local modules or your own target into a community frontend or made by yourself.


## Installing a module

Most front-end applications include an installation tool that fetches modules from official mirrors or custom repositories. You can explore available modules at: https://www.crosswire.org/sword/modules/

If you want to install one mannualy you can just download the zip files from the website, check the info (including the copyright of that module). And copy it to your sword folder.On Linux, this is typically `~/.sword`. On Windows, it might be located in `C:\Program Files\CrossWire\sword`.

After extracting the module ZIP file, you'll typically find two key directories: mods.d and modules. The mods.d directory contains configuration files (e.g., kjv.conf) that define module metadata and settings. The modules directory houses the actual content files, organized by type such as texts, comments, or lexdict depending on the module nature.

**Note:** If the module uses a compressed format like zText, the content will be stored in a compressed form. The SWORD engine will decompress and render the text when accessed.

## How to read a Module (SWORD 101)

This is the first piece of code you should run as learning this:


```cpp
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <swmgr.h>
#include <swmodule.h>
#include <markupfiltmgr.h>

using namespace::sword;

int main(int argc, char **argv)
{
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
```


## Resources

https://www.crosswire.org/sword/index.jsp

https://wiki.crosswire.org/Main_Page

https://www.crosswire.org/mailman/listinfo/sword-cvs

https://wiki.crosswire.org/Whiteboard
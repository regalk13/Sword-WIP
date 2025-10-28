# What is SWORD

"SWORD is an Application Programming Interface (API) for CrossWire modules. When referring to SWORD it is customary to use all uppercase. It is sometimes referred to as the SWORD engine."

## A CrossWire Module

A “module” in the SWORD ecosystem is essentially a content package: e.g., a Bible translation, a commentary, a lexicon/dictionary, a glossary, daily devotional, general book, map resource, etc. These modules are meant to be used by SWORD-compatible front-ends (programs) which load/display/search them (like Xiphos, BibleTime, etc). So this means if you develop a module poiting to a SWORD version if that version is implemented by some frontends they could read seamsly the content and use it.

Internally, it have:

-   ".conf" configuration file, which tells the SWORD engine where the data is, what driver to use, metadata like description, language, encoding, license, etc. [Read](https://www.crosswire.org/sword/develop/swordmodule/)

- The actual data files are in certain formats (legacy ones are like GBF, ThML and now OSIS XML) and then are imported/compiled (sometimes compressed) into the module form.

This means a common workflow (for a module creator) The workflow is obtain the source text, convert/markup it, import via SWORD utilities, create the .conf, test in front-ends, optionally submit to CrossWire for inclusion in their repository. And as end user you install this modules using the official repository, local modules or your own target into a community frontend or one made by yourself.


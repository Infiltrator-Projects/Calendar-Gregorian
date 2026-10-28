# Gregorian Calendar — provider architecture and Common integration

Calendar-Gregorian owns its executable chronology provider, Gregorian-specific presentation,
ICU adapter and model tests. Common owns public resource ABI, checked arithmetic, general
date coordinate algorithms, runtime discovery, dynamic loading, strings and validation.

Source uses the exact Common 1.19.80 submodule at dc4aac326964ca4400b6e21851d16eea674040c8.
The Makefile compiles Common's own static archive from that submodule and links against it.
No include/infiltratr headers and no src/{arithmetic,core,dynlib,temporal}.c copies remain.

The source ZIP and native .run installer snapshot that exact reviewed Common source,
allowing offline release installation without a separately provisioned Common runtime.
Independent provider fixtures, calendar math and ICU-specific behaviour remain local.
The historical SOURCE-MANIFEST.json records the origin of the original copied implementation
but no longer describes active Common source ownership. All release tests must pass before merge.

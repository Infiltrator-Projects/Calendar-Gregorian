# Gregorian Calendar — provider architecture and Common integration

Calendar-Gregorian owns its executable chronology provider, Gregorian-specific presentation,
ICU adapter and model tests. Common owns public resource ABI, checked arithmetic, general
date coordinate algorithms, runtime discovery, dynamic loading, strings and validation.

Source uses the authoritative Common submodule at the exact revision and version recorded in the current Makefile.
The Makefile compiles Common's own static archive from that submodule and links against it.
No include/infiltratr headers and no src/{arithmetic,core,dynlib,temporal}.c copies remain.

The text-only native installer fetches the exact provider and Common revisions over the network and verifies them before building. GitHub supplies its automatic source archive separately; the installer embeds no source or binary payload.
Independent provider fixtures, calendar math and ICU-specific behaviour remain local.
The historical SOURCE-MANIFEST.json records the origin of the original copied implementation
but no longer describes active Common source ownership. All release tests must pass before merge.

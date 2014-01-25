TEMPLATE = subdirs
SUBDIRS = polpcontrol \
    polpcore \
    plugins

polpcontrol.depends = polpcore
plugins.depends = polpcore

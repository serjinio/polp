TEMPLATE = subdirs
SUBDIRS = polpcontrol \
    polpcore \
    plugins \
    qcustomplot

polpcontrol.depends = polpcore
plugins.depends = polpcore

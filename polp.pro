TEMPLATE = subdirs
SUBDIRS = polpcore \
    qcustomplot \
    plugins \
    polpcontrol \

polpcontrol.depends = polpcore
plugins.depends = polpcore

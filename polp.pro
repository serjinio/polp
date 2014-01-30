TEMPLATE = subdirs
SUBDIRS = polpcore \
    qcustomplot \
    plugins \
    polpcontrol \

polpcore.depends = qcustomplot
polpcontrol.depends = polpcore
plugins.depends = polpcore

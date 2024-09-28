from pyavevae3demb import COMMON

x = COMMON()
x.ce = "/SITE-CABLE-AREA03"
print(x.mdb())
print(x.savework())
print(x.getwork())


from pyavevae3demb import DB
d = DB()
x = d.attributes()
print(x)
print(d.collectAllFor("/SITE-CABLE-AREA03"))
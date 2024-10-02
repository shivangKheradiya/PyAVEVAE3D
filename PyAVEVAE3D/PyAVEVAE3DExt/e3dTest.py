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
print(d.collectAllForElement("/SITE-CABLE-AREA03"))
print(d.collectAllFor( "PIPE BRAN" , "/SITE-PIPING-AREA01 /SITE-PIPING-AREA02"))

d.SetStringAttribute("/SITE-PIPING-AREA03", "Description", "Hiii")
d.SetBoolAttribute("/SITE-PIPING-AREA03", "Lock", True)
d.SetRealAttribute("=2013286668/53", "Number", 5)
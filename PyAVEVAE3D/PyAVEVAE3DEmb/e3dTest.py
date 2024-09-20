import pyavevae3demb
from pyavevae3demb import db

dir(pyavevae3demb)
print(pyavevae3demb.mdb())
mdb = pyavevae3demb.mdb()
print(mdb)
ce = pyavevae3demb.get_ce()
print(ce)
pyavevae3demb.set_ce("/100-B-2")

att = db.attributes()
print(att)
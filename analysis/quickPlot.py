import matplotlib.pyplot as plt
import numpy as np

#inputFile = open( "hits.30.n1000.csv" )
inputFile = open( "hits.150.n1000.csv" )

x, y, z, t = [], [], [], []
for line in inputFile:
  line = line.split( " " )

  # filter particles
  if line[0] != "opticalphoton":
    continue

  x.append( float( line[1] ) )
  y.append( float( line[2] ) )
  z.append( float( line[3] ) )
  t.append( float( line[4] ) )
x = np.array(x)
y = np.array(y)
z = np.array(z)
t = np.array(t)

# filter sensor edge
#edgeVal = np.mode( y )
edgeVal = -22.0
print( "Sensor edge y", edgeVal )
yMask = (y==edgeVal)
x = x[yMask]
z = z[yMask]
t = t[yMask]

print( min(t), max(t) )
#plt.scatter( y, z )
#plt.show()
#plt.hist2d( y, z )
#plt.show()
#plt.hist2d( y, z, weights=t )
#plt.show()
#plt.scatter( y[t>100], z[t>100] )
#plt.scatter( y[t<100], z[t<100] )
#plt.show()
#plt.hist( t )
#plt.show()
plt.hist2d( t, x )
plt.xlabel("t")
plt.ylabel("x")
plt.show()
#plt.hist2d( t, y )
#plt.xlabel("t")
#plt.ylabel("y")
#plt.show()
plt.hist2d( t, z )
plt.xlabel("t")
plt.ylabel("z")
plt.show()

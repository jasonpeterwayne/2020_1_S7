'''
Ch5 constant, variable, string
'''
#1.0 formated printing
age=20
name='swaroop'

print'{0} was {1} years old'.format(name,age)
print 'why is {0} playing with python'.format(name)

print '{0:.3f}'.format(1.0/3)
print '{0:_^11}'.format('hello')
print '{name} wrote {book}'.format(name='swaroop', book='a byte of python')

#2.0 escape character
print 'what\'s your name?'
print 'first line \n second line'
print r'first line \n second line'

#3.0 variables
i=5
print i
i+=1
print i

s=''' multiline string
This is second line'''

print s

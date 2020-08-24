'''
Ch6 Operators
'''

length = 5 #cm
width = 2.0 #cm

area = length * width

print 'Area is ', area, ' cm^2'
print 'Perimeter is ', 2*(length+width), 'cm'

input_literal='2-3+4*2'

print input_literal,'=', eval(input_literal)

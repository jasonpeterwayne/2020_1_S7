'''
Ch7 FlowControl
'''

number=23
running=True

#1.0 while and if statement
while running:
	guess = int(raw_input('Enter an integer: '))

	if(guess==number):
		print 'you guess it'
		running=False

	elif guess < number:
		print 'Low'
	else:
		print 'High'

print 'While test is over'

#2.0 for loop

for i in range(1,10,2):
	print i

print 'For loop test is completed'

#3.0 break and continue statements
while True:
	s=raw_input('Enter an literal:')
	if s=='quit':
		break
	if (len(s))<3:
		print 'Too small Input'
		continue
	print 'Input has sufficient length'

print 'The break/continue test is finished '

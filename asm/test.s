.name "bla"
.comment "bla bla"

start:
	st r1, 17
	live %2
	fork %6
	zjmp %:start


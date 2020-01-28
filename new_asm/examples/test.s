.name       "Batman"
.comment    "This city needs me"

loop:
        sti r1, %:live, %1
		fork %:loop
live:
        live %0
        ld %0, r2
        zjmp %:loop
		fork %:loop

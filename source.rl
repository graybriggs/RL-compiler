
######################
# Rudimentary Language
# Test Program
######################


# RL has no output so counting the occurances of
# fizz, buzz and fizzbuzz will have to suffice!

var fizz = 0
var buzz = 0
var fizzbuzz = 0

var counter = 0

while counter < 100 do

	if counter % 5 == 0 then
		if counter % 3 == 0 then
			fizzbuzz = fizzbuzz + 1
		else then
			buzz = buzz + 1
		end
	else then
		if counter % 3 then
			fizz = fizz + 1
	end

	counter = counter + 1
end
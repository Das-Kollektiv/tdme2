![LOGO](https://raw.githubusercontent.com/andreasdr/minitscript/master/resources/github/minitscript-logo.png)

# 1. Classes

Classes in MinitScript can be represented by maps. 
A constructed map with function assignments and/or definitions can be called object, see map section in 4.4.

Creating a object in MinitScript works by using map initializer plus () -> methodName function assignment, or () -> { console.dump($this) } inline function definition.
Please see the example below, which shows a object definition, which includes (private) member variables and member methods. 

Note that you can set member variables and member methods to private, if they are prefixed with a "-".


```
...
	#
	$car = {
		# member variables
		-wheelCount: 4,
		-color: "blue",
		-horsePower: 75,
		# member methods
		setWheelCount: ($wheelCount) -> 
			{
				$this.wheelCount = $wheelCount
			},
		setColor: ($color) ->
			{
				$this.color = $color
			},
		setHorsePower: ($horsePower) -> 
			{
				$this.horsePower = $horsePower
			},
		showMeWhatYouGot: () ->
			{
				console.printLine(
					"This amazing car has ", 
					$this.wheelCount,
					" wheels, is colored ", 
					$this.color,
					" with super nice ", 
					$this.horsePower,
					" horses in it"
				)
			},
		getProperties: (&$wheelCount, &$color, &$horsePower) -> 
			{
				$wheelCount = $this.wheelCount
				$color = $this.color
				$horsePower = $this.horsePower
			},
		-somePrivateFunction: () ->
			{
				console.printLine("This just shows a private member function")
			}
	}
	#
	console.dump($car)
	# arrr, lets see what kind of car we got
	$car->showMeWhatYouGot()
	# i want it in red with 3 wheels and 25 mighty horse power
	$car->setColor("red")
	$car->setWheelCount(3)
	$car->setHorsePower(25)
	# arrr, lets see what kind of car we got now!
	$car->showMeWhatYouGot()
	# lets get the properties
	$wheelCount = null
	$color = null
	$horsePower = null
	$car->getProperties($wheelCount, $color, $horsePower)
	console.printLine(
		"Car properties, wheels: ", 
		$wheelCount,
		", color: ", 
		$color,
		", horse power: ", 
		$horsePower
	)
	#...
```

If you want to assign a object member function later, see this example. Note that the first argument needs to be a reference or value by copy $this variable.
This argument maps to the object that your code is operating on in your object member function.
 
Be aware that value by copy variables usually require more instantiation time due to the copy that needs to be made of the variable from parent variable scope to function variable scope.  

```
...
function: setConvertible(&$this, $convertible)
	$this.convertible = $convertible
end

function: showMeWhatYouGot($this)
	$carType = "car"
	if ($this.convertible == true)
		$carType = "convertible"
	end
	console.printLine(
		"This amazing ", 
		$carType,
		" has ", 
		$this.wheelCount,
		" wheels, is colored ", 
		$this.color,
		" with super nice ", 
		$this.horsePower,
		" horses in it"
	)
end
	...
	#
	$car.convertible = false
	$car.setConvertible = () -> setConvertible
	$car.showMeWhatYouGot = () -> showMeWhatYouGot
	#
	console.dump($car)
	# I want a convertible, who doesn't?
	$car->setConvertible(true)
	# arrr, lets see what kind of car we got
	$car->showMeWhatYouGot()
	#...
```

# 2. Links

## 2.1. Language documentation
- [Syntax](./README-Syntax.md)
- [Data types, variables and constants](./README-DataTypes.md)
- [Flow control - if, elseif and else](./README-FlowControl-Conditions.md)
- [Flow control - switch, case and default](./README-FlowControl-Conditions2.md)
- [Flow control - forTime, forCondition, for and forEach](./README-FlowControl-Loops.md)
- [Flow control - exceptions](./README-FlowControl-Exceptions.md)
- [Functions](./README-Functions.md)
- [Lambda functions](./README-Lambda-Functions.md)
- [Classes](./README-Classes.md)
- [Modules](./README-Modules.md)
- [Built-in functions](./README-BuiltIn-Functions.md)
- [Built-in classes](./README-BuiltIn-Classes.md)
- [Operators](./README-Operators.md)
- [Constants](./README-Constants.md)

## 2.2. Other links

- MinitScript, see [README.md](../README.md)
- MinitScript - How to build, see [README-BuildingHowTo.md](../README-BuildingHowTo.md)
- MinitScript - How to use, see [README-Tools.md](../README-Tools.md)
- The Mindty Kollektiv [Discord Server](https://discord.gg/Na4ACaFD)

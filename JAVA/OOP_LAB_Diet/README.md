Diet
====

Write an application to manage a diet by means of nutritional values computation.

The application must allow the definition of raw materials, their use as ingredients for recipes, the definition of products and menus.

All the classes must be in the package "**diet**".

R1 - Raw Materials  

---------------------

The system works though the facade class **Food**.

To define a raw material, we can use the method **defineRawMaterial()** that accepts as arguments the name, the kilo-calories, the amount of proteins, carbohydrates (carbs), and fat; all the values refer to 100 grams of raw material. The name of the raw material can be considered unique.

To retrieve some information about the raw materials we can use the method **rawMaterials()** which returns a list of raw materials, sorted by name in alphabetic order. To get info about a specific material, we can use the method **getRawMaterial()** that accepts the name of the raw material and returns the corresponding raw material.

The raw materials returned by the above methods are objects implementing the interface **NutritionalElement**, which provides the getter methods **getName()**, **getCalories()**, **getProteins()**, **getCarbs()**, **getFat()**. Calories are expressed in KCal, while proteins, carbs, and fat are expressed in grams.

Moreover the interface includes the method **per100g()** that indicates whether the values refer to 100 grams of nutritional element or represent an absolute value. For raw materials the nutritional values are always expressed per 100 grams, therefore the method returns `true`.

R2 - Products
-------------

The diet may include also pre-packaged products (e.g. an ice cream or a snack). Products are defined by means of the method **defineProduct()** of class Food accepting as arguments the name, the kilo-calories, the amount of proteins, carbohydrates (carbs), and fat. Such values express the value for the whole product, therefore the method per100g() returns `false`. The name of the product can be considered unique.

To retrieve information about the products we can use the method **products()** of class Food that returns a collection of products sorted by name. To get information about a specific product, method **getProduct()** is available that accepts the name of the product and returns the corresponding object.

Both methods return the products as object implementing the interface _NutritionalElement_ (described in the previous requirement); the values are expressed for the whole product (i.e. the method _per100g()_ returns _false_).

R3 - Recipes
------------

Raw materials can be combined as ingredients of recipes. To define a recipe we can use the method **createRecipe()**, from class _Food_, that accepts as argument the name of the recipe. The name of the recipe can be considered unique.

A recipe is represented by an object of class **Recipe** that allows adding new ingredients by means of its method **addIngredient()** accepting as arguments the name of the raw material and the relative amount in grams.

Class Recipe implements the interface _NutritionalElement_ and the values are expressed per 100 grams.

To retrieve the information about the recipes we can use the method **recipes()**, of class _Food_, that returns a collection of recipes sorted by name. To get information regarding a specific recipe we can use the method **getRecipe()** that accepts as argument the name of the recipe and return the corresponding recipe. Both methods return recipes as _NutritionalElement_

The method **toString()** in class _Recipe_ returns a string that contains all the ingredients, one per per line, using the following format _"Material : ###.#"_ where _Material_ is the name of the raw material and _###.#_ is the relative quantity. Lines are all terminated with character _'\\n'_ and the ingredients must appear in the same order they have been added to the recipe.

*   **Warning**: While the sum of the amounts of ingredients (in grams) of a recipe is not necessarily equal to 100g, the nutritional values of the recipe must refer to an ideal portion of 100 grams.

R4 - Menu
---------

A menu consists of either portions of recipes or pre-packaged products.

Menus can be create with method **createMenu()** of class _Food_, that accepts as argument the name of the menu.

A menu is represented by class **Menu** that allows to add a portion of a recipe to the menu through method **addRecipe()** that accepts as argument the name of the recipe and the size of the portion, in grams.

To add an item of a pre-packaged product, class _Menu_ provides the method **addProduct()** that accepts as argument the name of the product.

Class _Menu_ implements the _NutritionalElement_ interface; in this case the values are referred to the whole menu.

DietExt
=======

Extended Requirements
=====================

Most interactions take place through the facade class **Takeaway**.

The application to manage a diet by means of nutritional values computation has been extended to provide services for ordering and delivering food (takeaway).

The application allow creating restaurants, registering users, making orders, etc.

All the classes must be in the package "**diet**".

R5 - Restaurant  

------------------

The **Restaurant** can be created providing a name and a reference to a _Food_ object so that all the ingredients, products, and recipes can be defined for each of the restaurants individually.

A restaurant can be identified by its name. Through the method **setHours()** working hours can be set for the restaurant. The methods accepts an array of strings (even number of elements) in the format _"HH:MM"_, so that the closing hours follow the opening hours (e.g., for a restaurant opened from 8:15 until 14:00 and from 19:00 until 00:00, arguments would be _"08:15", "14:00", "19:00", "00:00"_). Getter **getName()** returns a restaurant's name. Restaurant offer different menus, and they can be created through the method **createMenu()** having as argument menu's name and returning _Menu_ object.

Restaurants can be registered with the system using the method **addRestaurant()** of the facade class _Takeaway_. The method **restaurants()** returns the names of the registered restaurants.

R6 - Users
----------

A user is defined by providing its first name, last name, email and phone number to the method **registerUser()** that returns a **User** object. Getters are provided for all of the fields (**getFirstName()**, **getLastName()**, **getEmail()**, **getPhone()**), while setters are provided for the email and phone number only (**setEmail()**, **setPhone**). The string representation of a _User_ object returns the last name separated by a space and followed by the first name.

To retrieve information about the users we can use the method **users()** of class _Takeaway_ that returns a collection of users sorted first by their last name and then by first name.

R7 - Orders
-----------

A registered user can make an order at one of the available restaurants. For such purpose method **createOrder()** accepts as arguments the _User_ object making the order, restaurant's name (_String_) and the desired delivery time (hour and minute as integers). Furthermore, if for the given order delivery time is outside of the working hours for the restaurant, delivery time is set to the first successive opening hour (e.g., making an order for a restaurant having working hours from 8:15 until 14:00 and from 19:00 until 00:00, and asking for a delivery at 15:30, would result in having the delivery time set for 19:00).

An order can have three statuses: `ORDERED`, `READY`, `DELIVERED` accessible through setter and getter **setStatus()** and **getStatus()** (`ORDERED` by default). Furthermore, payment type for an order can be: `PAID`, `CASH`, `CARD`, accessible through setter and getter **setPaymentMethod()** and **getPaymentMethod()** (`CASH` by default).

Menus can be added to an order by calling the method **addMenus** and specifying the menu name (String) and the quantity (integer).

When an order is printed, it should be formatted as:

"RESTAURANT\_NAME, USER\_FIRST\_NAME USER\_LAST\_NAME : DELIVERY(HH:MM):
	MENU\_NAME\_1->MENU\_QUANTITY\_1
	...
	MENU\_NAME\_k->MENU\_QUANTITY\_k
"

The menus are sorted by menu name and are printed on different lines preceded by a tab (_'\\t'_).

*   **Warning**: If a certain menu is already added to an order, using it again as an argument in **addMenus()**, should overwrite the previously defined quantity

R8 - Information
----------------

To retrieve some information about the restaurants we can use the method **openedRestaurants()** that has one string argument in format "HH:MM" and returns a collection of _Restaurant_ that are opened at the given time, sorted by their name alphabetically. A restaurant is opened if there is at least one working hour segment such that the defined time is inside the range \[`open`, `close`).

Information about certain orders for a restaurant can be obtained through method **ordersWithStatus()** of the class Restaurant. Such method returns a String obtained by concatenating all orders satisfying the criteria.

Napoli, Judi Dench : (19:00):
	M6->1
Napoli, Ralph Fiennes : (19:00):
	M1->2
	M6->1

The list is sorted by name of restaurant, name of the user, and delivery time.

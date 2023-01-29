# Coding conventions

* ## Copyright Header
	It must be ensured that all code files have the following SPDX identifier at the top of each file
	```
	/* SPDX-License-Identifier: MIT */
	```

---

* ## Indentation
	All indentations must consist of tabs

---

* ## Naming
	* ### Variables
		Local variables should be implicit and unabbreviated except for specific cases, such as when a phrase is too long (like using `message` as `msg`)
		* #### global variables
			All global variables should have the prefix `as`
		* #### loop counter
			Use `i`, `j`, `k`, `l` in order for loop counters

	* ### Functions
		All functions should have the prefix `as` except for the main routine

---

* ## Bracket placement
	K&R style
	```
	while (i) {
		i++;
	}
	```	

---

* ## Type defining of structure 
	Please avoid using type defining structures and use structures with the `struct` keyword when declaring and defining instead
	```
	typedef struct mystruct, mystruct_t;
	mystruct_t s1; (✘)

	struct mystruct s1;(✔)
	```

---
	
* ## Comment
	Use `//` for temporary comments like todo

	Use `/*` and `*/` for other comments like description of code flows

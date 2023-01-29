# Coding conventions

* ## Copyright Header
	It must be ensured that all code files have the following SPDX identifier top of each file
	```
	/* SPDX-License-Identifier: MIT */
	```

---

* ## Indentation
	All indentations must consist of tab

---

* ## Naming
	* ### Variables
		In most of case local variables should be implicit and unabbreviated except specific case, representatively case that phrase is too long (like using `message` as `msg`)
		* #### global variables
			All global variables should have prefix `as`
		* #### loop counter
			Loop counter use `i`, `j`, `k`, `l` in order

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
	Please avoid type defining structure and use structure with struct keyword when declaring and defining
	```
	typedef struct mystruct, mystruct_t;
	mystruct_t s1; (✘)

	struct mystruct s1;(✔)
	```

---
	
* ## Comment
	temporary comments like todo use `//`

	other comments like description of code flows use `/*` and `*/`
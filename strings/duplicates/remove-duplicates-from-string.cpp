

/*
	Examples:
		Input:  azxxzy
		Output: ay
		First "azxxzy" is reduced to "azzy". The string "azzy" contains duplicates, 
		so it is further reduced to "ay".

		Input: geeksforgeeg
		Output: gksfor
		First "geeksforgeeg" is reduced to "gksforgg". The string "gksforgg" contains 
		duplicates, so it is further reduced to "gksfor".

		Input: caaabbbaacdddd
		Output: Empty String

		Input: acaaabbbacdddd
		Output: acac
*/

//Algorithm in O(n^2)
string removeDup(string str){
	
	int n = str.size();
	string res;
	
	int i = 0;
	while(i < n) {
		int j = i;

		//check adjacent pairs
		while(((i+1)<n) && (str[j] == str[i+1])) i++;

		//only one char
		if(i == j) res += str[i];
		i++;
	}
	
	//no change
	if(res.size() == n) return str;

	return removeDup(res);

}


//Algorithm in O(n)
string removeDup(string str){
	
	int n = str.size();
	string res;
	
	int i = 0;
	while(i < n) {
		int j = i;

		//check adjacent pairs
		while(((i+1)<n) && (str[j] == str[i+1])) i++;

		//only one char
		if(res.size() && (res.back() == str[j])) res.pop_back();
		else if(i == j) res += str[j];

		i++;
	}
	
	return res;

}


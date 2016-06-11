int binarySearch(int st,int end,int key){
	if(st>end)
		return -1;
		
	int mid=st+(end-st)/2;
	if(arr[mid]==key)
		return mid;
	else if(arr[mid]<key)
		return binarySearch(mid+1,end,key);
	return binarySearch(st,mid-1,key);
}

int binarySearchIti(int st,int end,int key){
	
	while(st<=end){
		int mid=st+(end-st)/2;
		if(arr[mid]==key){
			return mid;	
		}else if(arr[mid]<key){
			st=mid+1;
		}else{
			end=mid-1;
		}
	}
	return -1;
}

int firstOccurence(int st,int end,int key){

	while(st<=end){
		int mid=st+(end-st)/2;
		if(key<=arr1[mid]){
			end=mid;
			if(st==end){
				return mid;
			}
		}else if(arr1[mid]<key){
			st=mid+1;
		}
	}
	return -1;
}

int lastOccurence(int st,int end,int key){

	int index=-1;
	while(st<=end){
		int mid=st+(end-st)/2;
		if(key==arr1[mid]){
			index=mid;
			st=mid+1;
		}else if(arr1[mid]>key){
			end=mid-1;
		}else{
			st=mid+1;
		}
	}
	return index;
}
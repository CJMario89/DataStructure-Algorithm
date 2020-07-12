

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int num = nums1Size + nums2Size;
    int mid = 0;
    int odd = 0;
    double median = 0;
    if(num % 2 == 1){
        odd = 1;
        mid = (num / 2) + 1;
    }else{
        odd = 0;
        mid = num / 2;
    }
    int i = 0;
    int j = 0;
    
    int which = 0;
    int count = 0;
    while(count != mid){
        if(i == nums1Size){
            which = 2;
            j++;
            count++;
        }else if(j == nums2Size){
            which = 1;
            i++;
            count++;
        }else{
            if(nums1[i] <= nums2[j]){
                which = 1;
                i++;
                count++;
            }else{
                which = 2;
                j++;
                count++;
            }
        }
    }
    if(odd == 1){
        if(which == 1){
            median = nums1[i - 1];
        }else{
            median = nums2[j - 1];
        }
    }else{
        if(which == 1){
            if(i == nums1Size){
                median = (nums2[j] + nums1[i - 1]) / 2.0;
            }else if(j == nums2Size){
                median = (nums1[i] + nums1[i - 1]) / 2.0;
            }else{
                if(nums1[i] <= nums2[j]){
                    median = (nums1[i] + nums1[i - 1]) / 2.0;
                }else{
                    median = (nums2[j] + nums1[i - 1]) / 2.0;
                }
            }
        }else{
            if(i == nums1Size){
                median = (nums2[j] + nums2[j - 1]) / 2.0;
            }else if(j == nums2Size){
                median = (nums1[i] + nums2[j - 1]) / 2.0;
            }else{
                if(nums1[i] <= nums2[j]){
                    median = (nums1[i] + nums2[j - 1]) / 2.0;
                }else{
                    median = (nums2[j] + nums2[j - 1]) / 2.0;
                }
            }
        }
    }
    return median;
}

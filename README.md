# Food Stalls Tracking and Review System
[LiveDemo](https://youtu.be/dHpP9Q9Uipo)

## Project Overview
This **Tracking and Review System** helps UTAR Sungai Long Campus students and staffs discover nearby food stalls and make informed dining decisions.

The application consists of two core parts:
- Food Stalls Tracking
   - Track and manage information of at least 20 real food stalls adjacent to UTAR Sungai Long campus
   - Store stall details including menu items, prices, walking distance, operating hours, and etc.
   - Categorize stalls into Restaurants, Cafes, and Fast Food

- Food Stalls Review
   - Allow registered users to post ratings and reviews (1-5 stars)
   - Enable user to view ratings and reviews of any food stall
   - Modify or delete existing reviews
   - Persistent storage using .txt files as the database

The final deliverable is a working console-based application.

## Analysis Part
1. Food Stalls Tracking Part
   - Allow users (Staffs & Students) to track and manage the latest informations of available food stalls
   - Gather real informations from at least 20 food stalls 
2. Food Stalls Review Part
   - Allow users to give their ratings and reviews on the food stalls they have visited on a scale (e.g. 1 to 5 stars)
3. Store and Manage Data
   - Data saved in text files
4. User Interaction
   - Provide a user-friendly menu interface for:
     - Viewing available stalls
     - Adding reviews
     - Viewing existing review
     - Searching / Filtering stalls
    
## Project Structure
```bash
FoodStallsSystem/
├── main_menu.cpp          # Main program entry point
├── food_track.cpp
├── food_track.h/cpp       # Food Track class
├── store.cpp
├── store.h/cpp            # Store Class
├── review.cpp  
├── review.h/cpp           # Review class
│
├── restaurant_data.txt    # List of restaurants
├── cafe_data.txt          # List of cafes
├── fast_food_data.txt     # List of fast food stalls
│
├── ah_ma.txt              # Ah Ma menu
├── ah_ma_review.txt       # Ah Ma reviews
├── desa_ctk.txt           # Desa CTK menu
├── desa_review.txt        # Desa CTK reviews
├── ... (20+ stall files)
│
└── temp_review.txt        # Temporary review storage
```

## Navigation Flow
``` bash
Main Menu
├── 1. Food Stalls Tracking
│   ├── 1. Restaurants → Select Stall → Add/Modify/Delete/Calculate
│   ├── 2. Cafes → Select Stall → Add/Modify/Delete/Calculate
│   └── 3. Fast Food → Select Stall → Add/Modify/Delete/Calculate
│
└── 2. Review
    ├── 1. Restaurants → Select Stall → Give Comment/View Review/Modify/Delete
    ├── 2. Cafes → Select Stall → Give Comment/View Review/Modify/Delete
    └── 3. Fast Food → Select Stall → Give Comment/View Review/Modify/Delete
```

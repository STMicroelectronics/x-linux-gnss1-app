#!/usr/bin/python

# Copyright (c) 2024 STMicroelectronics. All rights reserved.
#
# This software component is licensed by ST under BSD 3-Clause license,
# the "License"; You may not use this file except in compliance with the
# License. You may obtain a copy of the License at:
#                     opensource.org/licenses/BSD-3-Clause

from math import *
import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter

if ( len(sys.argv) > 1 ):
	df = pd.read_csv(sys.argv[1])
else:
	#df = pd.read_csv("./test_data/gnss.csv")
        print("plz provde filename")
        exit()


def calc_dist(latid_prev,long_prev,latid_new,long_new):
	lon1,lat1,lon2,lat2 = map(radians, [long_prev,latid_prev,long_new,latid_new])
	dlon = lon2 - lon1
	dlat = lat2 - lat1
	a = sin(dlat/2)**2 + cos(lat1) * cos(lat2) * sin(dlon/2)**2
	c = 2 * asin(sqrt(a))
	r = 6371*1000 #in meters, Earth radius
	return c*r
	

df_gnss, df_filter = df.iloc[:,[1,2,3,4,5]], df.iloc[:,[6,7,8,9,10]]
df_dist_gnss = df_gnss.iloc[:,[0,1]]
df_dist_filter = df_filter.iloc[:,[0,1]]
row_size = df_dist_gnss.shape[0]
df_dist_gnss.loc[:,'dist_from_prev_gnss'] = 0.0
df_dist_filter.loc[:,'dist_from_prev_filt'] = 0.0

#For Debug 
#print(df_dist_gnss.head)
#print(df_dist_filter.head)

for i in range(0, (row_size-1)):
	df_dist_gnss.loc[i,'dist_from_prev_gnss'] = calc_dist(df_dist_gnss.loc[i,'latitude'],df_dist_gnss.loc[i,'longitude'],df_dist_gnss.loc[i+1,'latitude'],df_dist_gnss.loc[i+1,'longitude'])
	df_dist_filter.loc[i,'dist_from_prev_filt'] = calc_dist(df_dist_filter.loc[i,'filtered_latitude'],df_dist_filter.loc[i,'filtered_longitude'],df_dist_filter.loc[i+1,'filtered_latitude'],df_dist_filter.loc[i+1,'filtered_longitude'])

merge_df = pd.concat([df_dist_gnss.loc[:,'dist_from_prev_gnss'],df_dist_filter.loc[:,'dist_from_prev_filt']],axis=1) 
difference_df = pd.DataFrame(columns=['difference'])
difference_df['difference'] = merge_df["dist_from_prev_gnss"] - merge_df["dist_from_prev_filt"]
print(difference_df)

plt.plot(range(0,1000),merge_df.iloc[0:1000,0] )
plt.plot(range(0,1000),merge_df.iloc[0:1000,1] )

#uncomment any of below to see more data visualizations

#plt.plot(range(1000,2000),merge_df.iloc[1000:2000,0] )
#plt.plot(range(1000,2000),merge_df.iloc[1000:2000,1] )

#plt.plot(range(2000,3000),merge_df.iloc[2000:3000,0] )
#plt.plot(range(2000,3000),merge_df.iloc[2000:3000,1] )

#plt.plot(range(3000,row_size-1),merge_df.iloc[3000:row_size-1,0] )
#plt.plot(range(3000,row_size-1),merge_df.iloc[3000:row_size-1,1] )


plt.xlabel("time index")
plt.ylabel("distance(in meters)")

plt.show()


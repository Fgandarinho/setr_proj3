# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(setr_proj3)

zephyr_include_directories(MyEvents) #Add this line
zephyr_include_directories(MyMovies) #Add this line
target_include_directories(app PRIVATE src/MyEvents) #Add this line
target_include_directories(app PRIVATE src/MyMovies) #Add this line

target_sources(app PRIVATE src/main.c)

target_sources(app PRIVATE src/MyEvents/MyEvents.c) # Add module c source
target_sources(app PRIVATE src/MyMovies/MyMovies.c) # Add module c source
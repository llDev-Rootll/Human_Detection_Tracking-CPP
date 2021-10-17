# Human_Detection_Tracking-CPP
[![Build Status](https://app.travis-ci.com/aditiramadwar/Human_Detection_Tracking-CPP.svg?branch=Phase_1)](https://app.travis-ci.com/aditiramadwar/Human_Detection_Tracking-CPP)
[![Coverage Status](https://coveralls.io/repos/github/aditiramadwar/Human_Detection_Tracking-CPP/badge.svg?branch=Phase_1)](https://coveralls.io/github/aditiramadwar/Human_Detection_Tracking-CPP?branch=Phase_1)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

A C++ module to detect and track humans which outputs location information directly in a robot's reference frame.

## Introduction
This repository contains a robust human obstacle detector and tracker using a monocular camera, directly usable in a robot’s reference frame.

The initial design is as follows : 

<img alt="design" src="assets/design.gif" width="75%" />

*Fig 1 :  High Level Arhitecture Design*

## Currently under development in the "development" branch [here](https://github.com/llDev-Rootll/Human_Detection_Tracking-CPP/tree/development)

## Building for code coverage
```
sudo apt-get install lcov
cmake -D COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug ../
make
make code_coverage
```

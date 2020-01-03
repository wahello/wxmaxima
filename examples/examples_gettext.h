/* Automatically generated file using generate_code.sh from the .wxm examples           */
/* This file is part of wxMaxima, but read only by gettext allowing to translate the    */
/* example files.                                                                       */

/* Copyright (C) 2019 wxMaxima Team (https://wxMaxima-developers.github.io/wxmaxima/)   */

/* This program is free software; you can redistribute it and/or modify                 */
/* it under the terms of the GNU General Public License as published by                 */
/* the Free Software Foundation; either version 2 of the License, or                    */
/* (at your option) any later version.                                                  */

/* This program is distributed in the hope that it will be useful,                      */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of                       */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                        */
/* GNU General Public License for more details.                                         */

/* You should have received a copy of the GNU General Public License                    */
/* along with this program; if not, write to the Free Software                          */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA            */

#include <wx/wx.h>
#include <wx/string.h

wxString examples = 
L"/* [wxMaxima batch file version 1] [ DO NOT EDIT BY HAND! ]*/\n" 
L"/* [ Created with wxMaxima version 19.12.4-DevelopmentSnapshot ] */\n" 
L"/* [wxMaxima: title   start ]\n"  + _(
L"Visualizing 3D curves\n" 
) + L"   [wxMaxima: title   end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"wxplot_size:[1200,900]$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"Standard curves\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Maxima's default way of displaying 3d surfaces is optimized on fast display. In order to get a feeling for the shape of the curve it might help to right-click on it and press on the \"Pop-out interactively\" button which opens a window the curve can be rotated in:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"curve1:z=sin(x)*cos(y);\n" 
L"wxdraw3d(\n" 
L"    explicit(\n" 
L"        rhs(curve1),\n" 
L"        x,-3,3,\n" 
L"        y,-3,3\n" 
L"    )\n" 
L")$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Slower, but easier to understand the curve is if the surfacte isn't transparent:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"wxdraw3d(\n" 
L"    surface_hide=true,\n" 
L"    explicit(\n" 
L"        rhs(curve1),\n" 
L"        x,-3,3,\n" 
L"        y,-3,3\n" 
L"    )\n" 
L")$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Alternatively the curve can be made more colorful:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"wxdraw3d(\n" 
L"    enhanced3d=true,\n" 
L"    explicit(\n" 
L"        rhs(curve1),\n" 
L"        x,-3,3,\n" 
L"        y,-3,3\n" 
L"    )\n" 
L")$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"Contour lines\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"If not the shape, but the absolute heights are important maxima offers contour lines.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"wxdraw3d(\n" 
L"    surface_hide=true,\n" 
L"    color=\"#a0a0a0\",\n" 
L"    key=\"curve_1\",\n" 
L"    explicit(\n" 
L"        rhs(curve1),\n" 
L"        x,-3,3,\n" 
L"        y,-3,3\n" 
L"    ),\n" 
L"    contour='both,\n" 
L"    contour_levels=[-1,.2,1]\n" 
L")$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"In many cases the actual curve actually isn't important while the height values are. In this case it is possible to generate a top view without drawing the actual surface:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"wxdraw3d(\n" 
L"    explicit(\n" 
L"        rhs(curve1),\n" 
L"        x,-3,3,\n" 
L"        y,-3,3\n" 
L"    ),\n" 
L"    contour='map,\n" 
L"    contour_levels=[-1,.1,1]\n" 
L")$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"Moving pictures\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: subsect start ]\n"  + _(
L"In order to make the 3d shape easier to grasp\n" 
) + L"   [wxMaxima: subsect end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"As can easily be seen of one pops out the above images interactively and moves them the human brain is quite efficient in grasping the complete shape of a moving picture. wxMaxima allows to embed such a thing into the worksheet:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"wxanimate_autoplay:true$\n" 
L"wxanimate_framerate:10$\n" 
L"with_slider_draw3d(\n" 
L"    α,makelist(10*sin(2*π*t/20),t,0,40),\n" 
L"    view=[60,30+α],\n" 
L"    surface_hide=true,\n" 
L"    key=\"curve_1\",\n" 
L"    explicit(\n" 
L"        rhs(curve1),\n" 
L"        x,-3,3,\n" 
L"        y,-3,3\n" 
L"    ),\n" 
L"    contour='both,\n" 
L"    contour_levels=[-1,.2,1]\n" 
L")$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: subsect start ]\n"  + _(
L"In order to allow to read values more easily\n" 
) + L"   [wxMaxima: subsect end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Sometimes it isn't actually necessary to display the whole 3D shape and the height of the curve is more easy to read if one assigns the mouse's scroll wheel to the y coordinate.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"wxanimate_autoplay:false;\n" 
L"with_slider_draw(\n" 
L"    y_coord,makelist(i,i,-2,2,.1),\n" 
L"    key=\"z_{curve_1}\",\n" 
L"    explicit(\n" 
L"        subst(y=y_coord,rhs(curve1)),\n" 
L"        x,-3,3\n" 
L"    ),\n" 
L"    grid=[2,2],\n" 
L"    title=sconcat(\"y=\",y_coord),\n" 
L"    xlabel=\"x\",ylabel=\"z\",\n" 
L"    yrange=[-1,1]\n" 
L"),fpprintprec=3$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"In order to view this picture just click on it and move the mouse wheel; The fact that y needs to substituted into the equation to plot manually is a long-standing bug in maxima's makelist() command.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"\n" 
L"/* Old versions of Maxima abort on loading files that end in a comment. */\n" 
L"\"Created with wxMaxima 19.12.4-DevelopmentSnapshot\"$\n" 
L"/* [wxMaxima batch file version 1] [ DO NOT EDIT BY HAND! ]*/\n" 
L"/* [ Created with wxMaxima version 20.01.1 ] */\n" 
L"/* [wxMaxima: title   start ]\n"  + _(
L"Number formats\n" 
) + L"   [wxMaxima: title   end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"Floating-point numbers\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Most computers include floating-point units that make relatively-high-precision calculations very fast. If a number is input with a decimal dot or in the \"1e3\" notation maxima assumes one wants to use the kind of floats the machine supports out-of-the box:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"1.0;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"1000121012.10;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"1e9;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Any other number can be converted to a floating-point one using the float() keyword:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"float(10);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"float(10/3);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"The drawback the enhanced speed comes with is that using floating-point numbers come with inaccuracies that might hit when one least expects them. For example machine floats cannot exactly express seemingly simple numbers like 0.1:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"rationalize(0.1);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Another drawback is that mathematics is based on tha fact that two things that cancel each other out actually do so:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"0.1+0.01-0.1-0.01;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Rump and Wilkinson have provided warning examples of simple polynoms where this adds up to catastrophic errors quickly and it is surprising how often one encounters similar in real live including a big fraction of the glitches one can find in computer games.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Maxima allows to customize the format floating-point numbers are displayed in:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"load(\"engineering-format\")$\n" 
L"engineering_format_floats: true$\n" 
L"engineering_format_min: .01$\n" 
L"engineering_format_max: 1000$\n" 
L"fpprintprec: 6$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"0.1+0.01-0.1-0.01;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"float(π);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"float(π*10000);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"Bigfloats\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Maxima alternatively provides its own implementation of floating-point numbers that are slow (they have to be processed in software), but can be provided with any precision. Numbers can be converted to bifgfloats using the bfloat() command or by entering a \"b\" instead of an \"e\" when declaring the exponent:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"fpprintprec:0$\n" 
L"fpprec:100$\n" 
L"bfloat(%pi);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"rationalize(1b-1);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"If too low or to high a number of digits is displayed here when right-clicking on such a number opens up a menu that allows to customize this behavior.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"Exact numbers\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"The type of number maxima was written for is exact numbers instead. Maxima assumes any number that doesn't contain a decimal dot to be intended as being an exact number:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"1/10;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"π/4*3;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"sqrt(2)/2;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"exp(21/7);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"R_100=121*10^3;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Many hard-to-find errors can be avoided by using exact numbers. It is therefore wise to use exact numbers whereever possible and only to convert the results to floats using float() or bfloat():\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"sqrt(π)*3;\n" 
L"float(%);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"\n" 
L"/* Old versions of Maxima abort on loading files that end in a comment. */\n" 
L"\"Created with wxMaxima 20.01.1\"$\n" 
L"/* [wxMaxima batch file version 1] [ DO NOT EDIT BY HAND! ]*/\n" 
L"/* [ Created with wxMaxima version 20.01.1 ] */\n" 
L"/* [wxMaxima: title   start ]\n"  + _(
L"Solving equations\n" 
) + L"   [wxMaxima: title   end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Mathematics can be seen as a language consisting only of a rather small set of words and only a handful of grammatical rules. Both sets are carefully chosen, though, that by simply reformulating the question in many cases the answer can be found.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"If you are studying mathematics the good news is that solving equations is an art a computer can help with in many special cases but that often relies on human creativity for finding algorithms and ways.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"Simple equations\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"For many problems Maxima's solve() program instantly finds a list of solutions:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"pyth:c^2=a^2+b^2;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"sol1:solve(pyth,a);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Both solutions solve() offers are valied. We can pick any of them manually, for example:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"sol2:sol1[2];\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"By having given this equation a name (\"sol2\") we gained a way to re-use this equation later.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"This time the type of solutions we can get depends on the value of a which is why maxima asked about it. One can avoid asking questions by telling the answers to maxima's assume database:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"assume(a>0, b>0, c>0);\n" 
L"solve(sol2,b);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Solve also accepts lists as its arguments. In this case it will only find solutions if the following conditions are all met:\n" 
L" * The number of linearly independent equations matches the number of variables to solve to\n" 
L" * The solution doesn't completely change its form depending on the range one variable is in.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"eq2:a+2*b=10;\n" 
L"solve(\n" 
L"    [pyth,eq2],\n" 
L"    [a,b]\n" 
L");\n" 
L"rootscontract(%);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"By choosing [a,b] as the list of solution variables maxima is automatically told to eliminate these two variables on the right side of the equations, if possible.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"Re-using the solutions\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"As seen above the last equation displayed by maxima can be referenced by using the placeholder \"%\":\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"%;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Additionally have given nearly all equations names that allow to reference the whenever we need them. For example we can print them out again:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"sol2;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"We can use them as an input to solve:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"solve(sol2,b);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"/* [wxMaxima: question  start ] */\n" 
L"<mth><st>Is </st><mi>a</mi><st> positive, negative or zero?</st></mth>\n" 
L"/* [wxMaxima: question  end   ] */\n" 
L"/* [wxMaxima: answer  start ] */\n" 
L"p;\n" 
L"/* [wxMaxima: answer  end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"We can introduce (\"substitute\") them into other equations:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"E=m*c^2;\n" 
L"subst(pyth,%);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Additionally the left hand side and the right hand side can be extracted using the command lhs() and rhs() which allows to use the part left or right to to the \"=\" in a new equation:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"lhs(pyth);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"rhs(pyth);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"eq10:sin(δ)=rhs(pyth);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"Boiling it down to numbers\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"If in mathematics two things cancel each other out they do so exactly. The same isn't true with IEEE floating-point numbers like the ones the computer uses:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L".1;\n" 
L"%-.01;\n" 
L"%-.1;\n" 
L"%+.01;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Many computer programs are configured to show small numbers as \"0\" or only to show the first few digits after the decimal dot hoping that the rest is a rounding error that doesn't add up (see wilkinson's polynomial for an example where this happens quickly). Maxima's solve instead tries to replace floating-point numbers by the exact fraction it most likely means and warns about doing so:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"solve(x+.1=2,x);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Since it often is the general case that allows to learn about the fundamental mechanisms often a good approach is to solve everything numerically and to keep the actual numerical input values in a separate list like the following one:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"vals:[\n" 
L"    a=sqrt(1/2),\n" 
L"    b=sqrt(1/2),\n" 
L"    δ=π/2\n" 
L"];\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Whenever a numerical value is needed this list can be introduced into any equation:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"subst(vals,pyth);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"subst(vals,eq10);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"What if there exists no symbolical solution?\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Some solutions have never been assigned a name in mathematics. One popular example would be:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"eq2:cos(x)=x;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"solve() which tries to find an symbolical solution is bound to fail here and tells us how far it got:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"solve(eq2,x);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"In this case maxima offers several options to at least find the numerical values, two examples are given below:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"wxdraw2d(\n" 
L"    explicit(\n" 
L"        rhs(eq2)-lhs(eq2),\n" 
L"        x,-1,1\n" 
L"    ),\n" 
L"    grid=true\n" 
L")$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: subsect start ]\n"  + _(
L"mnewton\n" 
) + L"   [wxMaxima: subsect end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"mnewton uses a modified version of newton's method for finding a solution of a nonlinear, but differentiable, stetical and monotonic function near to a point (in this example 0.1)\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"load(\"mnewton\")$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"mnewton(eq2,x,.1);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: subsect start ]\n"  + _(
L"find_root\n" 
) + L"   [wxMaxima: subsect end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"find_root even works if the equation isn't differentiable and searches for a solution in between two points.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"find_root(eq2,x,-.001,1);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"\n" 
L"/* Old versions of Maxima abort on loading files that end in a comment. */\n" 
L"\"Created with wxMaxima 20.01.1\"$\n" 
L"/* [wxMaxima batch file version 1] [ DO NOT EDIT BY HAND! ]*/\n" 
L"/* [ Created with wxMaxima version 19.12.4-DevelopmentSnapshot ] */\n" 
L"/* [wxMaxima: title   start ]\n"  + _(
L"Tolerance calculations\n" 
) + L"   [wxMaxima: title   end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"If the outcome of an calculation depends on many factors determining manually which cases are the worst-case one is a manual and error-prone process. Alternatives to doing so are:\n" 
L" * Implementing a full-fledged interval arithmetics that automatically determines the range of the output depending on the ranges of the input parameters. Unfortunately doing so is so complex that any interval arithmetics is bound to work only in more or less trivial cases.\n" 
L" * A montecarlo analysis: All parameters are filled with random values out of their tolerance range. Then the calculation is repeated until the spread of the outcome can be seen.\n" 
L" * And systematically trying out all combinations at the edges of the tolerance space. \n" 
L"The last two of these methods are described here.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"The problem\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"A simple voltage divider of R_1 and R_2 is powered by a voltage source U_In. In which range can U_Out lie?\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: subsect start ]\n"  + _(
L"Mathematical description\n" 
) + L"   [wxMaxima: subsect end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"eq1: I=U_In/(R_1+R_2);\n" 
L"eq2: U_Out=I*R_2;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"These equations are simple enough that there is no need to use solve() to introduce them into each other:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"uout:subst(eq1,eq2);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: subsect start ]\n"  + _(
L"Input values that include a tolerance\n" 
) + L"   [wxMaxima: subsect end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"First we load the tolerance calculation package:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"load(\"wrstcse\")$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"The tolerance calculation package lets tol[n] tolerate between -1 and 1. tol[n] with the same n are coupled tolerances that share the same value. In theory the \"n\" doesn't need to be a number. But if it is a symbolic name one has to make sure this name is never assigned a value else tol[name] will be replaced by tol[<value of the variable \"name\">]\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Let's assume that R_1 is a 100Ω with 10% tolerance. R_2 is a 1000Ω resistor with 1% tolerance instead:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"vals1:[\n" 
L"    R_1=100*(1+.1*tol[1]),\n" 
L"    R_2=1000*(1+.01*tol[2])\n" 
L"];\n" 
L"wc_inputvalueranges(%);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"We can propose another set of values: Two resistors that are only 10% ones, but are guaranteed to always deviate into the same direction by the same percentage.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"vals2:[\n" 
L"    R_1=100*(1+.1*tol[1]),\n" 
L"    R_2=1000*(1+.1*tol[1])\n" 
L"];\n" 
L"wc_inputvalueranges(%);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: subsect start ]\n"  + _(
L"Print out the results\n" 
) + L"   [wxMaxima: subsect end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Just substituting the values into the equations provides us with the equation containing the real values and the tolerances in wrstcse's notation:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"subst(vals1,uout);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"If we just want to know the typical value we can do the following:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"wc_typicalvalues(subst(vals1,uout));\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"wc_typicalvalues(subst(vals2,uout));\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"We now want to test all combinations of minimum, typical or maximum value, instead.\n" 
L"First we tell maxima not to print a warning if a float is replaced by a fraction of the same value:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"ratprint:false;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Then we ask wrstcse to print out the tolerances of the right hand side of our equation \"uout\":\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"lhs(uout)=wc_mintypmax(subst(vals1,rhs(uout)));\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"This result is still - well, hard to interpret, because Maxima didn't know the value of U_In which is necessary to decide which of all the terms is the minimum and which is the maximum. But we can inform maxima about the necessary facts:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"assume(U_In>0);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"lhs(uout)=wc_mintypmax(subst(vals1,rhs(uout)));\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"lhs(uout)=wc_mintypmax(subst(vals2,rhs(uout)));\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"As we have guessed the 2nd voltage divider was the better one.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"Specifying complex tolerances\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Now we want to tell maxima that the voltage source provides a voltage between 4V and 6V, typically 4.5V. For doing this a specialized function exists:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"vals3:[\n" 
L"    R_1=100*(1+.1*tol[1]),\n" 
L"    R_2=1000*(1+.1*tol[1]),\n" 
L"    U_In=wc_mintypmax2tol(tol[3],4,4.5,6)    \n" 
L"];\n" 
L"wc_inputvalueranges(%);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"lhs(uout)=wc_mintypmax(subst(vals3,rhs(uout)));\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"Appending lists of tolerances\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"If it is necessary to append two lists of values with tolerances to each other without risking a collision of tol[n] that happen to have the same n in the two lists the following function can be used:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"vals4:[\n" 
L"    U_In=wc_mintypmax2tol(tol[1],4,4.5,6)    \n" 
L"];\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"vals5:wc_tolappend(vals1,vals4);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"wc_tolappend() appends values with tolerances and renumbers the tol[n]\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"Using a bigger or lower number of samples\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"By default the wrstcse package tests all combinations of 3 values per tol[n]: The minimum, the maximum and the typical value. If we only want to test 2 values (the minimum and the maximum) that might speed up lengthy calculations with many values that contain tolerances:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"lhs(uout)=wc_mintypmax(subst(vals5,rhs(uout)),2);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"Monte carlo analysis\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"This time we want the tolerance package to use 1000 random sets of values and to find the best and worst case that can be reached using these values:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"lhs(uout)=wc_mintypmax(subst(vals5,rhs(uout)),-1000);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"If this calculation is repeated it will naturally result in a different set of numers:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"lhs(uout)=wc_mintypmax(subst(vals5,rhs(uout)),-1000);\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: section start ]\n"  + _(
L"A ridicously advanced example\n" 
) + L"   [wxMaxima: section end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: subsect start ]\n"  + _(
L"Description of the problem\n" 
) + L"   [wxMaxima: subsect end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Someone constructs a magic drill that is guaranteed to generate holes that exactly meet 3 points. But that points unfortunately all have tolerances. We now are asked to produce images of the possible outcome.\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: comment start ]\n"  + _(
L"Round holes can be described as follows:\n" 
) + L"   [wxMaxima: comment end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"hole1:(x-x_1)^2+(y-y_1)^2=r^2;\n" 
L"hole2:(x-x_2)^2+(y-y_2)^2=r^2;\n" 
L"hole3:(x-x_3)^2+(y-y_3)^2=r^2;\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"solve([hole1,hole2,hole3],[x,y,r])$\n" 
L"sol1:%[2];\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: subsect start ]\n"  + _(
L"The coordinates of the points the wholes go through\n" 
) + L"   [wxMaxima: subsect end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"coords:[\n" 
L"    x_1=0+.04*tol[x1],y_1=0+.04*tol[y1],\n" 
L"    x_2=1+.04*tol[x2],y_2=0+.04*tol[y2],\n" 
L"    x_3=0+.04*tol[x3],y_3=1+.04*tol[y3]\n" 
L"];\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: subsect start ]\n"  + _(
L"Generating a list of 100 sets of possible values of \"coords\"\n" 
) + L"   [wxMaxima: subsect end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"lstOfCoords:wc_montecarlo(coords,100)$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: subsect start ]\n"  + _(
L"Plotting these lists\n" 
) + L"   [wxMaxima: subsect end   ] */\n"  
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"wxanimate_autoplay:true$\n" 
L"wxanimate_framerate:5$\n" 
L"with_slider_draw2d(\n" 
L"    i,lstOfCoords,\n" 
L"    point_type=2,grid=true,\n" 
L"    proportional_axes='xy,\n" 
L"    subst(\n" 
L"        i,\n" 
L"        [\n" 
L"            key=\"The 3 coordinates\",\n" 
L"            points([x_1,x_2,x_3],[y_1,y_2,y_3]),\n" 
L"            key=\"\",fill_color=\"#000000FF\",\n" 
L"            subst(\n" 
L"                sol1,\n" 
L"                ellipse(x,y,r,r,0,360)\n" 
L"            )\n" 
L"        ]\n" 
L"    ),\n" 
L"    xrange=[-.55,1.55],\n" 
L"    yrange=[-.55,1.55]\n" 
L")$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"/* [wxMaxima: input   start ] */\n" 
L"wxdraw2d(\n" 
L"    point_type=2,grid=true,\n" 
L"    proportional_axes='xy,\n" 
L"    makelist(\n" 
L"        subst(\n" 
L"            i,\n" 
L"            [\n" 
L"                points([x_1,x_2,x_3],[y_1,y_2,y_3]),\n" 
L"                key=\"\",fill_color=\"#000000FF\",\n" 
L"                subst(\n" 
L"                    sol1,\n" 
L"                    ellipse(x,y,r,r,0,360)\n" 
L"                )\n" 
L"            ]\n" 
L"        ),i,lstOfCoords),\n" 
L"    xrange=[-.55,1.55],\n" 
L"    yrange=[-.55,1.55]\n" 
L")$\n" 
L"/* [wxMaxima: input   end   ] */\n" 
L"\n" 
L"\n" 
L"\n" 
L"/* Old versions of Maxima abort on loading files that end in a comment. */\n" 
L"\"Created with wxMaxima 19.12.4-DevelopmentSnapshot\"$\n" 
" ";

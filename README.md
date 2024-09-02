# FarmingSimulator

<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![LinkedIn][linkedin-shield]][linkedin-url]




<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/PaulKokhanov1/BindingofIssacRemake">
    <img src="https://github.com/user-attachments/assets/75dbb687-e784-4154-bfd2-4cda963b26d3" alt="Logo" width="280" height="200">

  </a>

<h3 align="center">Fishing Simulator</h3>

  <p align="center">
    While still on the game dev journey, I noticed after talking to other developers they mentioned to also explore Unreal Engine 5 and C++, having previous knowledge of C++, I wanted to make a more technical feature/game while learning Unreal Engine 5.
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#goal">Goal</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li><a href="#genetic-algorithm">Genetic Algorithm</a></li>
    <li><a href="#game-design">Game Design</a></li>
    <li><a href="#bugs">Bugs</a></li>
    <li><a href="#next-steps">Next Steps</a></li>
    <li><a href="#conclusion">Conclusion</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- GOAL -->
## Goal
<div align="center">
  <a href="https://github.com/PaulKokhanov1/LunarLanderRL">
    

https://github.com/PaulKokhanov1/BindingofIssacRemake/assets/69466838/954386dc-9e36-4cc6-b870-c5261d8ef890


  </a>
</div>

My desire was to evolve my understanding of game development and coding using C# by building from scratch the popular dungeon crawler game "The Binding of Issac"

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* [![C++][Cpp.com]][Cpp-url]
* [![Unreal Engine 5][Unreal.com]][Unreal-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GENETIC ALGORITHM -->
## Genetic Algorithm

Within this section I will discuss the premise of a genetic algorithm, their use and a general overview of how to implement one. Then I will move on to explaining how I used a genetic algorithm in my fishing simulator.

### Overview

To begin, what is the premise of a GA? Essentially its based off of Darwin’s theory of evolution that encompasses how we evolve through a process of natural selection. Individuals who are typically the best at “competing” for a specific resources and adapting to environmental conditions are seen as favorable and then are chosen to evolve the lineage. In computer science, we use the idea of natural selection to evolve our solutions to a global optima.

Generally, genetic algorithms are a method for solving optimization problems by maintaining a population of candidate solutions and evolving them by applying a set of stochastic operators. Typically this process is continued until certain terminal conditions are met. GA’s are usually a good idea when you are looking for exact or approximate solutions to optimization or search problems. They allow for parallelism, they can provide multiple optimal solutions and are able to handle large search spaces, which is especially great in machine learning applications.

Now without going super in depth of the types of GA’s and all the various ways to implement one, we will stick with the original/first GA known as “Simple Genetic Algorithm” or SGA for short, developed in 1975.
Firstly, as mentioned before, GA’s hold a population of solutions from which individuals are chosen and “evolved” through the use of search operators (i.e, Recombination and Mutation), and SGA is no exception. The general scheme is as follows,

![image](https://github.com/user-attachments/assets/ac302ba1-7fa3-4d11-bc51-91e55a95be32)

We’ll briefly discuss each part by focusing on the below table,

![image](https://github.com/user-attachments/assets/9c5c6d4c-fc02-4e76-81bd-61b8a16979b5)

To start with **representation**, we need to encode a vector, ex: a solution from the parameter domain to the binary domain. To use “fancy” terms, we’d abstract the representation of the Phenotype to a genotype (i.e parameter -> Binary). Each “chromosome” (the individual bit) indicates the presence or absence of a feature, obviously this would not work out for features that may have more complex encoding’s and hence there are methods to represent our solutions using digits instead.

Moving onto **Parent Selection** (disregard the fact that I am straying from the order of the table). Now in order to quantify how good a solution is or isn’t we use a “fitness” function, Basically just think of it as a function that you plug in your solution to measure how close it is to your desired outcome. For example, we could have a function of some graph and we want to find variables x,y,z that yield the lowest value when plugged into that function, hence that is our “fitness” function. “Parent’s” (i.e solutions that are used to create new and better solutions) are selected proportionally to their fitness, so better fitness equals better chance of being selected. There are different methods to go about fitness proportional selection such as the ”roulette wheel technique” or “Baker’s Stochastic Universal Sampling algorithm” but ultimately they accomplish the same thing with certain pros and cons.

Then we proceed onto **Recombination**, which is where all the magic happens… , it’s the place where the storks get the babies to deliver to the parents. They’re different process to create offspring but in the case of binary representation we stick with 3 types: 1-point crossover, N-point crossover and Uniform Crossover, the latter being the most common. In Uniform crossover, for each gene we flip a fair coin (i.e 50/50 chance) to determine which parent the child inherits that specific chromosome. Then after going through each gene of child 1 we then make an inverse copy for the second child. See image below,

![image](https://github.com/user-attachments/assets/22539214-e4d6-4bdb-ad90-743be1d5905e)

**Mutation**, here is where we change the offspring to introduce “exploitation” into our algorithm, basically to potentially introduce small diversions that were not in the sample space given by the parents. With a pre-determined probability, we alter each gene (just flip the bit). The probability is usually set between 1/population_size and 1/chromosome_length.

Next up is **Survivor Selection**. 2 main approaches are used: Age-Based Selection, where it follows a FIFO idea, basically out with the old, in with the new and then Fitness-Based Selection, where the next generation is determined via each solutions “goodness”.

Now a couple things that I did not cover yet is **initialization** and **terminal conditions**. Initialization is done randomly, basically just generating random solutions or using simple search algorithms such as Depth-iterative search or Breath-first search. Then terminal conditions could be anything you really want, but common ones are: specified number of generation are reached, no improvement in the best individual for a specified number of generations or memory/time constraints
That’s really all there is to know about SGA and this should give you a better understanding of how I used a variation of SGA in my fishing simulator.



### Implementation/How it works

Now onto the meat and potatoes. In my game I really wanted to leverage my knowledge of algorithms and C++ to make a technical “game” whilst also keeping it simple enough to learn UE5 without overwhelming myself. Just like in my overview, I will go through each component of the GA and then mention brief pseudocode to explain the algorithm.

Firstly, the whole use of the genetic algorithm in my game was to develop an ecosystem depending on the “season”. So, I’d specify a season out of 4 possible candidates (for example, summer, fall, winter, spring) and then there would be an “ideal” fish for that season. An “ideal” fish would be one with specific traits, like color, size, speed, etc… , then the algorithm would slowly generate generations of solutions until the ideal solution is found. Thus my “fitness” function was simply calculating the absolute difference between the found and optimal solution. I adjusted the “tick” method within the pre-defined Unreal “Character” class to manage how often new generations were generated. Having said this, in order to expand the possible sample space and the possible fish’s I needed to use a real number representation method.

**Representation**: I used numbers 0 to 9 to represent each “gene/chromosome”, and the overall solution consisted of 6 concatenated digits. The 6 gene’s represented the following traits: Color, Size, Speed, Trait, Type, Intelligence. I was really struggling to think of features of fish as you can probably guess by me including “intelligence” of a fish. Anyways, Size, Speed and Intelligence mapped each digit to a float value between a range of 0 to 5.0, while Color, Trait and Type were mapped to specific strings. An example of a “trait” was “Aggressive”, and an example of a “type” was “Barracuda”. 

**Parent Selection**: In this implementation I opted for a tournament selection method as this removed premature convergence due to no one solution dominating the probability space of always being selected to be a parent. Rather in tournament selection, we use rank-based selection. The way I created this selection was by first choosing 100 random solutions from my population, then sorting them based on rank (which is determined by the fitness), selecting the top 50 to then be later used to create the offspring. 

**Recombination**: I opted to use the simple arithmetic crossover strategy as I was dealing with a real-valued genetic algorithm. The simple arithmetic crossover method is as follows: having parents <x_1, x_2, …> & <y_1, y_2,…> starting from a random gene (k) we produce the 1st child as so, 

![image](https://github.com/user-attachments/assets/cbfe36d3-ee7f-44ef-ad38-52ca26581acd)

And then reversed for the 2nd child. As an example,

![image](https://github.com/user-attachments/assets/8e4c6443-207b-40ea-a231-3586579162b2)

**Mutation**: Analogous to the method used in SGA (i.e bit-flipping) the method I used (called: Uniform Mutation) is randomly drawing a value from a predetermined interval (which in my case was digits 0 -> 9) and replacing that gene with a specified probability, which in my case was a value of 0.8 (or 80%).

**Survivor Selection**: Nothing too fancy, I decided to select the next generation based on fitness instead of replacing all the older generation with the newer one. In this fashion I was able to retain the best individuals from older generations while discarding poor candidates from the offspring.

**Initialization**: I randomly generated a population of solutions by choosing random values for each gene of the solution from the digits 0 to 9. My Terminal conditions were once the best individual did not change for a predetermined amount of generations then the algorithm would stop iterating.

Now to give a brief overview of the pseudocode:
1. Generate 150 solutions by concatenating 6 randomly chosen digits 
- Find fitness immediately for each solution
2. While not meeting terminal conditions:
- Sort current generation of solutions
- Select Parents using Tournament Selection, selecting 100 random solutions
- Sort the 100 solutions and choose top 50
- Using top 50, generate two child using simple arithmetic crossover per randomly selected pair (different combination each time)
- Mutate each child with a probability of altering any one gene of 80%
- Select survivors from Parents and offspring based on their fitness
Overall, I think this was an interesting way to implement some of the knowledge gained from one of my classes into a field that I love to explore, so even though it was not the most complex thing, I think it allowed me to demonstrate my C++ and algorithms knowledge while also giving me time to learn how to use UE5.


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GAME DESIGN -->
## Game Design

Here is where I’ll talk about the game/simulator itself and the mechanics implemented and how this was all coded via C++ instead of blueprints. This isn’t to say blueprints are something that I want to avoid but ultimately this project was to show/use my knowledge in C++, so I opted for avoiding blueprints plus it was more intuitive for me considering I was coming from a Unity background. 

Anyways, lets layout the scope of this project:

-	Create a “game” to be able to catch different types of fish being generated by a genetic algorithm.

Working from here, I started by first creating the genetic algorithm, as described above. Next, I worked on simple character movement and handling inputs. Then, there was the line casting mechanic which projects a forward moving bubble that changes to green whenever you are over a position that is able to be “fished” in. Also changing input context mappings to an input mapping handling the “fishing and catching” part. Finally, creating and updating a widget to display the fish’s features once you’ve caught a fish. This may be confusing so see the below video for a good reference,

[Include Video of full game mechanic]

**Input Handling**: To manage inputs, movement and “fishing Stamina”, I used the enhanced input system provided by UE5, this involved declaring the appropriate UPROPERTY input actions and Input mapping context within a C++ Player Controller class and then making the necessary Input Action’s and Input Mapping Context modules within the editor. After assigning the modules to the class references, I would bind all possible input actions to an EnhancedInputComponent and create the needed classes to handle each input. Furthermore, to avoid removing specific input actions or rebinding individual keys, I created a couple input context mappings that allowed me to easily change between different key bindings depending on whether I was in the process of “waiting to catch a fish” or simply moving around and casting the line. For example, whilst “waiting to catch a fish” using the spacebar would reel in your line to “catch” the fish, however this was the same button used to cast the reel in the first place. Thus, to avoid needing to remap that specific key binding, which through C++ was not necessary the easiest given the limited documentation, I instead simply changed the input mapping context.

**Character Stamina**: To experiment with the tick method and managing a character feature that could deplete and replenish over time, I included “Fishing Stamina”. Basically, you’d use up a bulk of stamina by throwing the line and over time your stamina would drain slowly as you wait for a fish. However, once you’ve reeled in your line, the stamina would regenerate at a constant rate. This may seem like a silly feature, but I think it would allow for possible future power-ups and making the “fishing simulator” more fast paced. 

**Casting**: Once the player presses and holds the spacebar, a red sphere will appear in front of the character that moves in the forward vector direction of the character, the sphere will change to green once it is in a appropriate position to cast the line. The inspiration came from trajectory prediction seen in various video games, for example, when a character wants to throw a grenade they sometime have the option to see its trajectory for a more accurate throw. To handle determining when the “line” was in an appropriate location, I simply use a box collision object within my scene over the necessary fishing locations. Then I’d change the material of the sphere to a green color once OnOverlapStart was called and change the material back to red once OnOverlapEnd was called.

**Fishing**: As the player releases the line in a fishing location, there will be a “buoy” object created on the surface of the water to indicate the position of where the individual is casting. At this moment is where I also swap the input mapping context to the “Fishing” one, which swaps the spacebar to allow the player to “catch” a fish and display the widget.

**Catching and Fish Description**: Due to time constraints and the joy of going back to school… oh how fun… I didn’t have the time to implement the feature of catching a fish, as in showing the bobbing of the buoy and indicating the player should reel in the line once the buoy goes underwater. So instead, once the player presses the space bar, the code will take one random solution from the current genetic algorithm generation to be our “caught” fish. This mechanic, means that as the player waits longer into the “season” the chances of catching the optimal fish for that season increases and then begins changing again once the season changes. The widget itself is not too complicated as it retrieves information from different TMap’s of each feature and displays them on a text box in the center of the screen. Which is hidden after the player either presses [X] or attempts to cast the line again.


<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- BUGS -->
## Bugs

In this section, I’d like to briefly explain a couple bugs within the game and possible solutions that may or may not work.

### Player getting stuck between rooms



### Tears immediately being destroyed when shooting when player is at the top wall



<!-- NEXT STEPS -->
## Next Steps


<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONCLUSION -->
## Conclusion


<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTACT -->
## Contact

Paul Kokhanov - [Website](https://paulkokhanov.com/) - paul.kokhanov@gmail.com

Project Link: [https://github.com/PaulKokhanov1/FarmingSimulator](https://github.com/PaulKokhanov1/FarmingSimulator)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [GGameDev](https://www.youtube.com/watch?v=dS5AUaYFcdw&ab_channel=GGameDev)
* [Cooperative & Adaptive Algorithms Course](https://uwaterloo.ca/academic-calendar/undergraduate-studies/catalog#/courses/view/65ce3a9ed3ef75325eb08133)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/github_username/repo_name.svg?style=for-the-badge
[contributors-url]: https://github.com/github_username/repo_name/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/github_username/repo_name.svg?style=for-the-badge
[forks-url]: https://github.com/github_username/repo_name/network/members
[stars-shield]: https://img.shields.io/github/stars/github_username/repo_name.svg?style=for-the-badge
[stars-url]: https://github.com/github_username/repo_name/stargazers
[issues-shield]: https://img.shields.io/github/issues/github_username/repo_name.svg?style=for-the-badge
[issues-url]: https://github.com/github_username/repo_name/issues
[license-shield]: https://img.shields.io/github/license/github_username/repo_name.svg?style=for-the-badge
[license-url]: https://github.com/github_username/repo_name/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/paulkokhanov
[product-screenshot]: https://github.com/PaulKokhanov1/LunarLanderRL/assets/69466838/6ed735d2-09d7-42f3-bfe3-01473ff121c9
[product-screenshot-original]:https://github.com/PaulKokhanov1/LunarLanderRL/assets/69466838/efdba43a-cc5b-4a62-b447-c9cd2fac6ba2

[Next.js]: https://img.shields.io/badge/next.js-000000?style=for-the-badge&logo=nextdotjs&logoColor=white
[Next-url]: https://nextjs.org/
[React.js]: https://img.shields.io/badge/React-20232A?style=for-the-badge&logo=react&logoColor=61DAFB
[React-url]: https://reactjs.org/
[Vue.js]: https://img.shields.io/badge/Vue.js-35495E?style=for-the-badge&logo=vuedotjs&logoColor=4FC08D
[Vue-url]: https://vuejs.org/
[Unreal.com]: https://img.shields.io/badge/Unreal_Engine_5-blue?style=for-the-badge&logo=unrealengine&logoColor=black
[unreal-url]: https://www.unrealengine.com/en-US/unreal-engine-5
[Cpp.com]: https://img.shields.io/badge/C%2B%2B-white?style=for-the-badge&logo=cplusplus&logoColor=blue
[Cpp-url]: https://isocpp.org/
[CSharp.com]: https://img.shields.io/badge/C%23-%23512BD4?style=for-the-badge&logo=csharp&logoColor=white
[CSharp-url]: https://marketplace.visualstudio.com/items?itemName=ms-dotnettools.csdevkit
[Unity.com]: https://img.shields.io/badge/unity-0769AD?style=for-the-badge&logo=unity&logoColor=white
[Unity-url]: https://unity.com/
[Gimp.com]: https://img.shields.io/badge/GIMP-FFE01B?style=for-the-badge&logo=gimp&logoColor=%235C5543&color=FFE01B
[Gimp-url]: https://www.gimp.org/

/**
 * Extreme Edge Cases
 * CS 241 - Fall 2019
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "camelCaser.h"
#include "camelCaser_tests.h"

#include "camelCaser_ref_utils.h"

/*
 * Testing function for various implementations of camelCaser.
 *
 * @param  camelCaser   A pointer to the target camelCaser function.
 * @param  destroy      A pointer to the function that destroys camelCaser
 * 			output.
 * @return              Correctness of the program (0 for wrong, 1 for correct).
 */
int test_camelCaser(char **(*camelCaser)(const char *),
                    void (*destroy)(char **)) {
    // TODO: Return 1 if the passed in function works properly; 0 if it doesn't.

    char *input = "welcome to ++cs241. 333333333333.";
    char **output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);

    input = "1111111111. 222222222222. 3333333333333. 444444444444444. 55555555555555.";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);

    input = "The Heisenbug is an incredible creature. Facenovel servers get \
      their power from its indeterminism. Code smell can be ignored with \
      INCREDIBLE use of air freshener. God objects are the new religion.";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);

    input = "One thing we know is that good code is generally modular - it \
    consists of discrete “units” of functionality that are only responsible \
    for very specific and certain behavior. In our case, working with C, \
    these “units” are functions.";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);


    input = "Using this system, all my code is highly decoupled (meaning easy \
      to re-use) because it all already has two users - its clients, and its \
      test rigs. Classes typically resist the transition from one user to two, \
      then the rest are easy. I make reuse easy as a side-effect of coding \
      very fast.";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);


    input = "Your manager at Facenovel, to celebrate Hump Day, has asked all of \
      the interns to implement a brand new camelCaser to convert sentences \
      into camelCase. To give you a chance to earn your return offer, he also \
      assigned you to write test cases for all the other interns’ \
      implementations of camelCaser, with the implementations hidden from you.";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);

    input = "[][][][][][][][][][][][][][][]";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);

    input = " CS100A, also known as CS106A ACE, is a 1-unit supplementary \
      section designed to build a stronger foundation in computer science. \
      Students participating in ACE will attend an additional weekly section \
      and participate in exam review sessions and individual tutoring. Section \
      will take place Thursdays 1:30-3:30pm PT in person. ACE is one of the \
      School of Engineering’s Equity and Inclusion Initiatives. We especially \
      want to provide an opportunity for students who come from educationally \
      disadvantaged backgrounds or for anyone who feels they might need \
      additional support in order to succeed. We limit enrollment to enable \
      small classes that allow students to have one-on-one interactions with \
      the TA. If you are interested in joining the ACE section, please apply \
      at this link due Friday, September 24th at 5pm PT. If you have any \
      questions about ACE, feel free to reach out to Brian Zeng (CS106A ACE TA) \
      at bzeng313@stanford.edu. ";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);

    input = "You are allowed to discuss general approaches and issues with \
      other students in the class. It's also fine to give other students help \
      finding bugs if they are stuck, or to answer general questions, such as \
      \"what is the meaning of this field in an inode?\" But, any code you \
      submit must be written by you, from scratch, without consulting existing \
      solutions. We reserve the right to use computer software such as MOSS to \
      analyze material that you submit in order to detect duplication with other\
      students or existing solutions. A general way to think about this is that \
      if a particular activity significantly short-circuits the learning \
      process (it saves you time but reduces the amount you learn and/or figure \
      out on your own), or if it misrepresents your capabilities or accomplishments, \
      then it is probably an Honor Code violation.";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);

    input = "Many assignments in this course will read your output and grade \
      them. This means that having stray prints may cause you to randomly fail \
      tests. Furthermore, excessive logging prints can reduce the performance \
      of your code, which can also cause you to fail tests. Therefore, you \
      should always check your code to make sure you don’t have random prints \
      in your code. Instead of writing print statements and removing them \
      repeatedly, a recommended strategy is to use the following function below \
      to perform logging:";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);

    input = "==++++++++++++++. 1-2507-0thf9q930q3hfisdnfoq2-934y829- 58y945pqio \
      jfpaiu29-4712945630985i1[0-4i91237591h5928y5091274-1209joi]";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);

    input = "Students who may need an academic accommodation based on the impact\
      of a disability must initiate the request with the Student Disability \
      Resource Center (SDRC) located within the Office of Accessible Education \
      (OAE). SDRC staff will evaluate the request with required documentation, \
      recommend reasonable accommodations, and prepare an Accommodation Letter \
      for faculty dated in the current quarter in which the request is being \
      made. Students should contact the SDRC as soon as possible since timely \
      notice is needed to coordinate accommodations. The OAE is located at 563 \
      Salvatierra Walk (phone: 723-1066).";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);


    input = "As I have these \"aha!\" moments (mentioned in 2 above) I follow \
      Kent's practice of adding them to the ToDoList. It took my stupid head \
      quite some time to realize that the TODO list is actually a list of \
      Micro-Stories, which I constantly prioritize (since I am the customer \
      at this level). Following AlistairCockburn's insight that Stories are \
      promises to have a conversation with the customer, I see, then, that the \
      Micro-Stories in the TODO list are a promise to have a conversation with \
      myself (and, here is the weird bit) to have a conversation with the code \
      (since it gives me feedback - it tells me things - and TDD tunes me in to \
      listening to the code). ";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);

    input = "!%&%&$*#&)(^#)(*^)&@^*@&%$(#%&#^%#(!)(!^*$%#^)#)(*#&*($%(#$&#())))";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);

    input = "In the spirit of collegial and cooperative learning, you are free \
      to discuss ideas and approaches with other students, and then implement \
      the solution yourself. The key is this: all the code you submit you should \
      type in and get working yourself. In particular, it is not ok to share or \
      paste in someone else's code or get code from a previous quarter. It is \
      not ok to look at someone else's code. You should not be looking at another \
      student's homework code. For discussion or tying out ideas, the many lecture \
      examples work well and of course it's fine for everyone to look at and \
      experiment with that code. Web search: it's fine if you search the web to \
      find the right 2 line phrase to solve something, like \"sort strings\" - \
      programmers do that sort of search all the time, and finding and using short \
      phrases like that is fine. Do not, however, search for a whole homework \
      function and paste in what you find. We want you to write that code. The \
      Computer Science department produces many honor code cases at Stanford. \
      This is not because CS is a magnet for cheating; it's just that online \
      submissions provide a large body of evidence, and computer science has \
      tools which do an extremely good job of finding cheating. If you think a \
      bit of collaboration may have crossed the line, please mention the \
      collaboration at the top of your homework file so your section leader \
      knows. This will most likely not change anything about your grade, you're \
      just getting it on the record. You can never get in honor code trouble \
      for collaboration clearly described in this way. As mentioned above, CS106A \
      exams will very much resemble the homework problems. So that's an additional \
      reason you need to author and understand your own code. On a related note, \
      when you are done with a homework - please don't post your code on the internet! \
      That causes problems for us and for people trying to learn the material later. ";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);

    input = "...................................................................";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);

    input = ". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \
      . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .";
    output = camelCaser(input);
    printf("check_output test: %d\n", check_output(input, output));
    destroy(output);
    return 1;
}

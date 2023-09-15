 //Let forms load first before checking
 document.addEventListener('DOMContentLoaded', function()
 {
     // Check multiple choice correct answer function on click
     document.querySelector('input[id="option-1776"]').addEventListener('click',
         function (event)
         {
            //Append node with message
            const node = document.createElement('response');
            const textnode = document.createTextNode('Correct, History Buff!');
            node.appendChild(textnode);
            document.getElementById("multiChoice").appendChild(node);
            //Change button color to green
            document.getElementById(event.target.id).style.backgroundColor = 'green';
            event.preventDefault();
         });

     // Check multiple choice inccorrect answers on click
     // variable for all wrong answers
     let answers = document.querySelectorAll('input[id="option-1865"], input[id="option-1777"], input[id="option-1609"], input[id="option-none"]');
     answers.forEach(answer => {
         answer.addEventListener('click',
             function (event)
             {
                //Change background color to red
                document.getElementById(event.target.id).style.backgroundColor = 'red';
                //Append node with message
                const node = document.createElement('response');
                const textnode = document.createTextNode('Incorrect! Try reading a book!');
                node.appendChild(textnode);
                document.getElementById("multiChoice").appendChild(node);
                event.preventDefault();
             });
     });

     // Check free form answer function on click
     document.querySelector('form[id="freeForm"]').addEventListener('submit',
         function (event)
         {
             let answer = document.querySelector('#free-form').value;
             let converted = answer.toLowerCase();
             if (converted == 'reuben')
             {
                //Change text field color color to green
                document.getElementById('free-form').style.backgroundColor = 'green';
                //Append node with message
                const node = document.createElement('response');
                const textnode = document.createTextNode('Correct, Sandwich Boss!');
                node.appendChild(textnode);
                document.getElementById("FreeFormDiv").appendChild(node);
                event.preventDefault();
             }
             else
             {
                //Change text field to red
                document.getElementById('free-form').style.backgroundColor = 'red';
                //Append node with message
                const node = document.createElement('response');
                const textnode = document.createTextNode('Incorrect!');
                node.appendChild(textnode);
                document.getElementById("FreeFormDiv").appendChild(node);
                event.preventDefault();
             }
         });
 });

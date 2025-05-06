// Define quiz questions, options, and correct answers
var questions = [];

function loadJSON(callback) {
    $.getJSON('questions.json', function(data) {
      callback(data);
    });
}
  
  // Initialize variables
  var currentQuestionIndex = 0;
  var score = 0;
  
  // Display current question and options
  function displayQuestion() {
    var currentQuestion = questions[currentQuestionIndex];
    $('#question').text(currentQuestion.question);
    $('#options').empty();
    currentQuestion.options.forEach(function(option) {
      $('#options').append('<li><input type="radio" name="option" value="' + option + '"> ' + option + '</li>');
    });
  }
  
  // Check answer and provide feedback
  function checkAnswer() {
    var selectedOption = $('input[name="option"]:checked').val();
    if (selectedOption === questions[currentQuestionIndex].answer) {
      $('#feedback').text('Correct!');
      score++;
    } else {
      $('#feedback').text('Incorrect. The correct answer is: ' + questions[currentQuestionIndex].answer);
    }
    $('#score').text(score);
    $('#feedback-container').show();
    $('#submit-btn').hide();
  }
  
  // Proceed to next question
  function nextQuestion() {
    currentQuestionIndex++;
    if (currentQuestionIndex < questions.length) {
      $('#feedback-container').hide();
      $('#submit-btn').show();
      displayQuestion();
    } else {
      // End of quiz
      $('#question-container').hide();
      $('#feedback-container').hide();
      $('#score-container').show();
    }
  }
  
  // Event handlers
  $(document).ready(function() {
    questions = loadJSON(function(data) {
        questions = data
        displayQuestion();
    });
  
    $('#submit-btn').click(function() {
      checkAnswer();
    });
  
    $('#next-btn').click(function() {
      nextQuestion();
    });
  });
  
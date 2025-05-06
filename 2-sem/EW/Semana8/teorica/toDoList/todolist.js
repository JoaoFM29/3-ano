$(function() {
    // Add Task button click event
    $('#addTaskBtn').click(function() {
      var taskInput = $('#taskInput').val();
      if (taskInput !== '') {
        $('#taskList').append('<li>' + taskInput + '<button class="deleteTaskBtn">Delete</button></li>');
        $('#taskInput').val('');
      }
    });
  
    // Delete Task button click event
    $(document).on('click', '.deleteTaskBtn', function() {
      $(this).parent().remove();
    });
  });
  
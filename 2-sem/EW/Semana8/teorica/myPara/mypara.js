$(function() {
    // Add Task button click event
    $('#addPara').click(function() {
      var paraIn = $('#paraIn').val();
      if (paraIn !== '') {
        event.preventDefault()
        $('#paraList').append('<li>' + paraIn + '</li>');
        $('#paraIn').val('');
      }
    });
  
    // Delete Task button click event
    $(document).on('click', '.deleteTaskBtn', function() {
      $(this).parent().remove();
    });
  });
  
$(document).ready(function() {
    // Add More Files button click event
    $('#addMoreBtn').click(function() {
      var fileInput = $('<input type="file" name="files[]" multiple>');
      $('#uploadForm').append(fileInput);
    });
  
    // File input change event
    $('#uploadForm').on('change', 'input[type="file"]', function() {
      var files = $(this).prop('files');
      var fileList = $('#fileList');
  
      fileList.empty();
  
      $.each(files, function(index, file) {
        fileList.append('<li>' + file.name + '</li>');
      });
    });
  });
  
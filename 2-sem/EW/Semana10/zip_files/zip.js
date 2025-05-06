const fs = require('fs');
const JSZip = require('jszip');

// Read the zip file
const zipFilePath = 'gficheiros.zip'; // Replace with the path to your zip file
const zipData = fs.readFileSync(zipFilePath);

// Process the zip file
JSZip.loadAsync(zipData).then(zip => {
    // Iterate over each file in the zip file
    zip.forEach((relativePath, zipEntry) => {
        console.log('File:', relativePath);

        // Extract the file content
        /* zipEntry.async('string').then(content => {
            console.log('Content:', content);
        }); */
    });
}).catch(err => {
    console.error('Error processing zip file:', err);
});

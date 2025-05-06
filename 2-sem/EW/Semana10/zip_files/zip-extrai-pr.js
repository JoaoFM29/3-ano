const fs = require('fs');
const JSZip = require('jszip');
var xml2js = require('xml2js');

// Read the zip file
const zipFilePath = 'gficheiros.zip'; // Replace with the path to your zip file
const zipData = fs.readFileSync(zipFilePath);

// Process the zip file
JSZip.loadAsync(zipData).then(zip => {
    // Iterate over each file in the zip file
    zip.file('PR.xml').async('string')
        .then(xmlContent => {
            var parser = new xml2js.Parser();
            parser.parseString(xmlContent, function (err, result) {
                console.dir(result);
                console.dir(result.PR.meta);
            })
        })
        .catch(err => {
            console.error(`Error extracting PR.xml from ZIP file:`, err);
        });
}).catch(err => {
    console.error('Error processing zip file:', err);
});

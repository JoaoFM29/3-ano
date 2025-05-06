namespace BirdBoxFull.Server.Services.ServicoProduto
{
    using Stripe;
    using System;
    using System.Net;
    using System.Net.Mail;

    public class EmailSenderService : IEmailSenderService
    {
        public void SendAuctionEndedEmail(string toAddress, string auctionTitle,bool sucesso)
        {
            // Set your email configuration
            string smtpServer = "smtp.gmail.com";
            int smtpPort = 587; // Example port; adjust as needed
            string smtpUsername = "jonugoro@gmail.com";
            string smtpPassword = "dkod lncy osiq eryw";

            // Create a MailMessage object
            MailMessage mail = new MailMessage();
            mail.From = new MailAddress(smtpUsername);
            mail.To.Add(new MailAddress(toAddress));
            mail.Subject = "Leilão Terminou";
            if (sucesso == true)
            {
                mail.Body = $"O Leilão '{auctionTitle}' terminou com sucesso.";
            }
            else
            {
                mail.Body = $"Não houve compradores para o Leilão '{auctionTitle}', tente novamente no futuro :)";
            }
            

            // Configure SMTP client
            SmtpClient smtpClient = new SmtpClient(smtpServer);
            smtpClient.Port = smtpPort;
            smtpClient.Credentials = new NetworkCredential(smtpUsername, smtpPassword);
            smtpClient.EnableSsl = true; // Enable SSL if your SMTP server requires it

            // Send the email
            try
            {
                smtpClient.Send(mail);
                Console.WriteLine("Email sent successfully!");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error sending email: {ex.Message}");
            }
            finally
            {
                mail.Dispose();
                smtpClient.Dispose();
            }
        }

        public void SendDetails(string email, string v)
        {
            // Set your email configuration
            string smtpServer = "smtp.gmail.com";
            int smtpPort = 587; // Example port; adjust as needed
            string smtpUsername = "jonugoro@gmail.com";
            string smtpPassword = "dkod lncy osiq eryw";

            // Create a MailMessage object
            MailMessage mail = new MailMessage();
            mail.From = new MailAddress(smtpUsername);
            mail.To.Add(new MailAddress(email));
            mail.Subject = v;
            mail.Body = "Obrigado por utilizar a plataforma 'Bird Box Auction', deve enviar a sua peça para a seguinte morada: \n" +
                "Cidade: Braga \n" +
                "Rua: São Vitor \n" +
                "Código-Postal: 4781-123 \n" +
                "\n" +
                "Obrigado e aguardamos a sua encomenda!";


            // Configure SMTP client
            SmtpClient smtpClient = new SmtpClient(smtpServer);
            smtpClient.Port = smtpPort;
            smtpClient.Credentials = new NetworkCredential(smtpUsername, smtpPassword);
            smtpClient.EnableSsl = true; // Enable SSL if your SMTP server requires it

            // Send the email
            try
            {
                smtpClient.Send(mail);
                Console.WriteLine("Email sent successfully!");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error sending email: {ex.Message}");
            }
            finally
            {
                mail.Dispose();
                smtpClient.Dispose();
            }
        }
    }

}

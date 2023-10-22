import ReduxProvider from "@/redux/provider";
import "./globals.css";
import { Inter } from "next/font/google";

export const metadata = {
  title: "MeetMe",
  description: "Связываем миры, создавая встречи",
};

const inter = Inter({
  subsets: ["latin"],
  display: "swap",
});

export default function RootLayout({ children }) {
  return (
    <html lang="en" className={inter.className}>
      <head>
        <link rel="manifest" href="js13kpwa.webmanifest" />
      </head>
      <body>
        <ReduxProvider>{children}</ReduxProvider>
      </body>
    </html>
  );
}

/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    "./pages/**/*.{js,ts,jsx,tsx,mdx}",
    "./components/**/*.{js,ts,jsx,tsx,mdx}",
    "./app/**/*.{js,ts,jsx,tsx,mdx}",
    "./ui/**/*.{js,ts,jsx,tsx,mdx}",
  ],
  theme: {
    colors: {
      transparent: "transparent",
      current: "currentColor",
      "bg-gray": "#F5F5F5",
      "text-gray": "#8F8F8F",
      "bg-white": "#FFFFFF",
      "text-black": "#1C274C",
      "text-active": "#0156FE",
      "text-tag": "#4665CD",
      "text-error": "#DC143C",
    },
  },
  plugins: [],
};

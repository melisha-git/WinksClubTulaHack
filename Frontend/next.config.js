/** @type {import('next').NextConfig} */
const nextConfig = {
  images: {
    remotePatterns: [
      {
        protocol: "https",
        hostname: "static.tildacdn.com",
        port: "",
        pathname: "/tild3366-6230-4162-b636-353136366132/**",
      },
      {
        protocol: "https",
        hostname: "img.icons8.com",
        port: "",
        pathname: "/ios-glyphs/**",
      },
    ],
  },
};

module.exports = nextConfig;

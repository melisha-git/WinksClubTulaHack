import Image from "next/image";

export default function ImgRoundedUI({ src, alt, size }) {
  return (
    <Image
      src={src}
      height={size}
      width={size}
      className=" w-14 h-14 rounded-full"
      alt={alt}
    />
  );
}

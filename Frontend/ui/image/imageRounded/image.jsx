import Image from "next/image";

export default function ImgRoundedUI({ src, alt }) {
  return (
    <Image
      src={src}
      height={56}
      width={56}
      className=" w-14 h-14 rounded-full"
      alt={alt}
    />
  );
}

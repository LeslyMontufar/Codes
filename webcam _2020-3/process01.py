import cv2
import numpy as np
import matplotlib.pyplot as plt

def convolve(im, omega):
    im = np.pad(im, ((0,1), (0,1))) # zero pad últimas linha e coluna
    spi = np.fft.fft2(im)
    spf = np.fft.fft2(omega, s=im.shape)
    g = spi*spf
    f = np.fft.ifft2(g)
    return np.real(f)[1:,1:] # elimina as primeiras linha e coluna

kernel = {
    'identity': np.array([[0,0,0],[0,1,0],[0,0,0]], dtype=float),
    'edge detection': np.array([[1,0,-1],[0,0,0],[-1,0,1]], dtype=float),
    'laplacian': np.array([[0,-1,0],[-1,4,-1],[0,-1,0]], dtype=float),
    'laplacian w/ diagonals': np.array([[-1,-1,-1],[-1,8,-1],[-1,-1,-1]], dtype=float),
    'laplacian of gaussian': np.array([[0,0,-1,0,0],[0,-1,-2,-1,0],[-1,-2,16,-2,-1],[0,-1,-2,-1,0],[0,0,-1,0,0]], dtype=float),
    'scharr': np.array([[-3, 0, 3],[-10,0,10],[-3, 0, 3]], dtype=float),
    'sobel edge horizontal': np.array([[-1,-2,-1],[0,0,0],[1,2,1]], dtype=float),
    'sobel edge vertical': np.array([[-1,0,1],[-2,0,2],[-1,0,1]], dtype=float),
    'line detection horizontal': np.array([[-1,-1,-1],[2,2,2],[-1,-1,-1]], dtype=float),
    'line detection vertical': np.array([[-1,2,-1],[-1,2,-1],[-1,2,-1]], dtype=float),
    'line detection 45°': np.array([[-1,-1,2],[-1,2,-1],[2,-1,-1]], dtype=float),
    'line detection 135°': np.array([[2,-1,-1],[-1,2,-1],[-1,-1,2]], dtype=float),
    'box blur': (1/9)*np.ones((3,3), dtype=float),
    'gaussian blur 3x3': (1/16)*np.array([[1,2,1],[2,4,2],[1,2,1]], dtype=float),
    'gaussian blur 5x5': (1/256)*np.array([[1,4,6,4,1],[4,16,24,16,4],[6,24,36,24,6],[4,16,24,16,4],[1,4,6,4,1]], dtype=float),
    'sharpen': np.array([[0,-1,0],[-1,5,-1],[0,-1,0]], dtype=float),
    'unsharp masking': (-1/256)*np.array([[1,4,6,4,1],[4,16,24,16,4],[6,24,-476,24,6],[4,16,24,16,4],[1,4,6,4,1]], dtype=float),
}

def variance_of_laplacian(image):
    # filtro passa-alta laplaciano para a deteccao de bordas e assim verificar se está borrado
	return cv2.Laplacian(image, cv2.CV_64F).var()

def deteccaoBlur(foco, limiar):
    if foco < limiar:
        text = "borrada"
    else:
        text = "normal"
    return (text+": "+str((foco-limiar>=0)*'+')+ format(foco-limiar, ".2f"))


state = 'normal'
file = "img\\imagem.png"
image =[]
cap = cv2.VideoCapture(0)

def webcam(blurdetection = True, nucleo = 'identity', limiar = 35):
    cap = cv2.VideoCapture(0)
    if (cap.isOpened()== False): 
        print("Error opening video stream or file")
    while(cap.isOpened()):
        ret, frame = cap.read()
        if ret == True:
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            conv = np.uint8(np.round(convolve(gray, kernel[nucleo])))
            # Tranforma em imagem de tres canais para colocar o texto em vermelho
            image = cv2.merge([conv,conv,conv])
            # cv2.imshow('Bordas', cv2.Laplacian(image, cv2.CV_64F))
            if blurdetection:
                image = cv2.putText(image, deteccaoBlur(variance_of_laplacian(image),limiar), (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 255), 3)
            cv2.imshow('Frame', image)
                        
            # Teclado
            key = cv2.waitKey(25)
            if key == ord('q') or key == 27:
                liberar()
                break
            elif key == ord('s'):
                cv2.imwrite(file,conv)
                break

        # Se não houver conexão, encerra
        else:
            break

def liberar():
    cap.release()
    cv2.destroyAllWindows()
